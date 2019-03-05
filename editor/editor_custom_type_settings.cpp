/*************************************************************************/
/*  editor_custom_type_settings.cpp                                      */
/*************************************************************************/
/*                       This file is part of:                           */
/*                           GODOT ENGINE                                */
/*                      https://godotengine.org                          */
/*************************************************************************/
/* Copyright (c) 2007-2018 Juan Linietsky, Ariel Manzur.                 */
/* Copyright (c) 2014-2018 Godot Engine contributors (cf. AUTHORS.md)    */
/*                                                                       */
/* Permission is hereby granted, free of charge, to any person obtaining */
/* a copy of this software and associated documentation files (the       */
/* "Software"), to deal in the Software without restriction, including   */
/* without limitation the rights to use, copy, modify, merge, publish,   */
/* distribute, sublicense, and/or sell copies of the Software, and to    */
/* permit persons to whom the Software is furnished to do so, subject to */
/* the following conditions:                                             */
/*                                                                       */
/* The above copyright notice and this permission notice shall be        */
/* included in all copies or substantial portions of the Software.       */
/*                                                                       */
/* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,       */
/* EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF    */
/* MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.*/
/* IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY  */
/* CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,  */
/* TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE     */
/* SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.                */
/*************************************************************************/

#include "editor_custom_type_settings.h"

#include "core/global_constants.h"
#include "core/project_settings.h"
#include "editor/editor_node.h"
#include "modules/class_type/class_type.h"
#include "scene/main/viewport.h"
#include "scene/resources/packed_scene.h"

#define PREVIEW_LIST_MAX_SIZE 10

void EditorCustomTypeSettings::_notification(int p_what) {

	if (p_what == NOTIFICATION_ENTER_TREE) {

		List<String> afn;
		ResourceLoader::get_recognized_extensions_for_type("PackedScene", &afn);

		EditorFileDialog *file_dialog = custom_type_add_path->get_file_dialog();

		for (List<String>::Element *E = afn.front(); E; E = E->next()) {
			file_dialog->add_filter("*." + E->get());
		}
	}
}

bool EditorCustomTypeSettings::_custom_type_name_is_valid(const String &p_name, String *r_error) {

	if (!p_name.is_valid_identifier()) {
		if (r_error)
			*r_error = TTR("Invalid name.") + "\n" + TTR("Valid characters:") + " a-z, A-Z, 0-9 or _";

		return false;
	}

	if (ClassDB::class_exists(p_name)) {
		if (r_error)
			*r_error = TTR("Invalid name. Must not collide with an existing engine class name.");

		return false;
	}

	if (ScriptServer::is_global_class(p_name) && !ClassDB::is_parent_class(ScriptServer::get_global_class_base(p_name), "Node")) {
		if (r_error)
			*r_error = TTR("Invalid name. Must not collide with an existing non-Node script class name.");

		return false;
	}

	for (int i = 0; i < Variant::VARIANT_MAX; i++) {
		if (Variant::get_type_name(Variant::Type(i)) == p_name) {
			if (r_error)
				*r_error = TTR("Invalid name. Must not collide with an existing buit-in type name.");

			return false;
		}
	}

	for (int i = 0; i < GlobalConstants::get_global_constant_count(); i++) {
		if (GlobalConstants::get_global_constant_name(i) == p_name) {
			if (r_error)
				*r_error = TTR("Invalid name. Must not collide with an existing global constant name.");

			return false;
		}
	}

	return true;
}

void EditorCustomTypeSettings::_custom_type_add() {

	custom_type_add(custom_type_add_name->get_text(), custom_type_add_path->get_line_edit()->get_text());

	custom_type_add_path->get_line_edit()->set_text("");
	custom_type_add_name->set_text("");
}

void EditorCustomTypeSettings::_custom_type_selected() {

	TreeItem *ti = tree->get_selected();

	if (!ti)
		return;

	selected_custom_type = ti->get_text(0);
}

void EditorCustomTypeSettings::_custom_type_edited() {

	if (updating_custom_type)
		return;

	TreeItem *ti = tree->get_edited();
	int column = tree->get_edited_column();

	UndoRedo *undo_redo = EditorNode::get_undo_redo();

	if (column == 0) {
		String name = ti->get_text(0);
		String old_name = selected_custom_type;

		if (name == old_name)
			return;

		String error;
		if (!_custom_type_name_is_valid(name, &error)) {
			ti->set_text(0, old_name);
			EditorNode::get_singleton()->show_warning(error);
			return;
		}

		Dictionary old_types = ProjectSettings::get_singleton()->get_setting(property_name);
		if (old_types.has(name)) {
			ti->set_text(0, old_name);
			EditorNode::get_singleton()->show_warning(vformat(TTR("CustomType '%s' already exists!"), name));
			return;
		}

		updating_custom_type = true;

		Dictionary types = old_types.duplicate();
		Dictionary named_type = old_types[old_name].duplicate();
		types.erase(old_name);
		types[name] = named_type;

		undo_redo->create_action(TTR("Rename CustomType"));

		undo_redo->add_do_property(ProjectSettings::get_singleton(), property_name, types);
		undo_redo->add_undo_property(ProjectSettings::get_singleton(), property_name, old_types);

		undo_redo->add_do_method(this, "call_deferred", "update_custom_types");
		undo_redo->add_undo_method(this, "call_deferred", "update_custom_types");

		undo_redo->add_do_method(this, "emit_signal", custom_type_changed);
		undo_redo->add_undo_method(this, "emit_signal", custom_type_changed);

		undo_redo->commit_action();

		selected_custom_type = name;
	}

	updating_custom_type = false;
}

void EditorCustomTypeSettings::_custom_type_button_pressed(Object *p_item, int p_column, int p_button) {

	TreeItem *ti = Object::cast_to<TreeItem>(p_item);

	String name = ti->get_text(0);

	UndoRedo *undo_redo = EditorNode::get_undo_redo();

	switch (p_button) {
		case BUTTON_OPEN: {
			_custom_type_open(ti->get_text(1));
		} break;
		case BUTTON_DELETE: {

			Ref<ClassType> type = ClassType::from_name(name);
			if (type->is_script_class())
				break;

			Dictionary old_types = ProjectSettings::get_singleton()->get(property_name);
			Dictionary types = old_types.duplicate();
			types.erase(name);

			undo_redo->create_action(TTR("Remove CustomType"));

			undo_redo->add_do_property(ProjectSettings::get_singleton(), property_name, types);
			undo_redo->add_undo_property(ProjectSettings::get_singleton(), property_name, old_types);

			undo_redo->add_do_method(this, "update_custom_types");
			undo_redo->add_undo_method(this, "update_custom_types");

			undo_redo->add_do_method(this, "emit_signal", custom_type_changed);
			undo_redo->add_undo_method(this, "emit_signal", custom_type_changed);

			undo_redo->commit_action();
		} break;
	}
}

void EditorCustomTypeSettings::_custom_type_activated() {
	TreeItem *ti = tree->get_selected();
	if (!ti)
		return;
	_custom_type_open(ti->get_text(1));
}

void EditorCustomTypeSettings::_custom_type_open(const String &fpath) {
	String type = ResourceLoader::get_resource_type(fpath);
	if (type == "PackedScene" || type == "Script") {
		EditorNode::get_singleton()->open_request(fpath);
	}
	ProjectSettingsEditor::get_singleton()->hide();
}

void EditorCustomTypeSettings::_custom_type_file_callback(const String &p_path) {

	StringName name = custom_type_get_base_file(p_path);
	custom_type_add_name->set_text(p_path.get_file().get_basename());
}

StringName EditorCustomTypeSettings::custom_type_get_base(const StringName &p_name) const {
	Ref<ClassType> type = ClassType::from_name(p_name);
	if (!type->exists())
		return StringName();
	Ref<ClassType> base = type->get_type_parent();
	if (!base->exists())
		return StringName();
	return base->get_name();

	if (p_name == StringName() || !custom_types.has(p_name))
		return StringName();
}

StringName EditorCustomTypeSettings::custom_type_get_base_file(const String &p_path) const {
	return custom_type_get_base(custom_type_get_name(p_path));
}

StringName EditorCustomTypeSettings::custom_type_get_name(const String &p_path) const {
	return path_map[p_path];
}

Object *EditorCustomTypeSettings::custom_type_instance(const StringName &p_name) {
	Ref<ClassType> type = ClassType::from_name(p_name);
	if (type->get_res().is_null())
		return NULL;

	return _create_custom_type(custom_types[p_name].path);
}

bool EditorCustomTypeSettings::custom_type_is_parent(const StringName &p_name, const StringName &p_inherits) {
	if (!custom_types.has(p_name))
		return false;

	return EditorNode::get_editor_data().script_class_is_parent(custom_type_get_base(p_name), p_inherits);
}

Object *EditorCustomTypeSettings::_create_custom_type(const String &p_path) {
	Ref<ClassType> type = ClassType::from_path(p_path);
	if (type.is_null())
		return NULL;
	return type->instance();
}

void EditorCustomTypeSettings::_update_tree() {

	tree->clear();
	TreeItem *root = tree->create_item();

	List<StringName> types;
	ClassType::get_script_class_list(&types);
	ClassType::get_custom_type_list(&types);
	types.sort_custom<StringName::AlphCompare>();

	for (List<StringName>::Element *E = types.front(); E; E = E->next()) {

		StringName name = E->get();

		if (name == StringName())
			continue;

		Ref<ClassType> type = ClassType::from_name(name);

		String path = type->get_path();

		custom_types[name] = CustomTypeInfo(name, path);

		String source;
		if (type->is_script_class())
			source = "Script Class";
		else if (type->is_custom_type())
			source = "Script Class";

		TreeItem *item = tree->create_item(root);
		item->set_text(0, name);
		item->set_editable(0, true);

		item->set_text(1, path);
		item->set_selectable(1, true);

		item->set_text(2, path);
		item->set_selectable(2, true);

		item->add_button(3, get_icon("FileList", "EditorIcons"), BUTTON_OPEN, type->is_script_class());
		item->add_button(3, get_icon("Remove", "EditorIcons"), BUTTON_DELETE, type->is_script_class());
		item->set_selectable(3, true);
	}
}

void EditorCustomTypeSettings::update_custom_types() {

	if (updating_custom_type)
		return;

	updating_custom_type = true;

	custom_types.clear();

	Dictionary dict;
	if (ProjectSettings::get_singleton()->has_setting(property_name))
		dict = ProjectSettings::get_singleton()->get(property_name);

	List<Variant> names;
	dict.get_key_list(&names);

	for (List<Variant>::Element *E = names.front(); E; E = E->next()) {

		StringName name = E->get();
		Dictionary data = dict[name];

		if (name == StringName())
			continue;

		String path = data["path"];

		custom_types[name] = CustomTypeInfo(name, path);
		path_map[path] = name;
	}

	updating_custom_type = false;
}

void EditorCustomTypeSettings::custom_type_add(const String &p_name, const String &p_path, const String &p_icon_path) {

	String name = p_name;

	String error;
	if (!_custom_type_name_is_valid(name, &error)) {
		EditorNode::get_singleton()->show_warning(error);
		return;
	}

	String path = p_path;
	if (!FileAccess::exists(path)) {
		EditorNode::get_singleton()->show_warning(TTR("Invalid Path.") + "\n" + TTR("File does not exist."));
		return;
	}

	if (!path.begins_with("res://")) {
		EditorNode::get_singleton()->show_warning(TTR("Invalid Path.") + "\n" + TTR("Not in resource path."));
		return;
	}

	String icon_path = p_icon_path;
	if (icon_path.length()) {
		if (!FileAccess::exists(icon_path)) {
			EditorNode::get_singleton()->show_warning(TTR("Invalid Icon Path.") + "\n" + TTR("File does not exist."));
			return;
		}

		if (!icon_path.begins_with("res://")) {
			EditorNode::get_singleton()->show_warning(TTR("Invalid Icon Path.") + "\n" + TTR("Not in resource path."));
			return;
		}
	}

	UndoRedo *undo_redo = EditorNode::get_singleton()->get_undo_redo();

	undo_redo->create_action(TTR("Add CustomType"));

	Dictionary old_types = ProjectSettings::get_singleton()->get_setting(property_name);
	ERR_FAIL_COND(old_types.has(name));

	Dictionary types = old_types.duplicate();
	Dictionary named_type;
	named_type["path"] = path;
	types[name] = named_type;

	undo_redo->add_do_property(ProjectSettings::get_singleton(), property_name, types);
	undo_redo->add_undo_property(ProjectSettings::get_singleton(), property_name, old_types);

	undo_redo->add_do_method(this, "update_custom_types");
	undo_redo->add_undo_method(this, "update_custom_types");

	undo_redo->add_do_method(this, "emit_signal", custom_type_changed);
	undo_redo->add_undo_method(this, "emit_signal", custom_type_changed);

	undo_redo->commit_action();
}

void EditorCustomTypeSettings::custom_type_remove(const String &p_name) {

	String name = "custom_type/" + p_name;

	UndoRedo *undo_redo = EditorNode::get_singleton()->get_undo_redo();

	int order = ProjectSettings::get_singleton()->get_order(name);

	undo_redo->create_action(TTR("Remove CustomType"));

	undo_redo->add_do_property(ProjectSettings::get_singleton(), name, Variant());

	undo_redo->add_undo_property(ProjectSettings::get_singleton(), name, ProjectSettings::get_singleton()->get(name));
	undo_redo->add_undo_method(ProjectSettings::get_singleton(), "set_persisting", name, true);
	undo_redo->add_undo_method(ProjectSettings::get_singleton(), "set_order", order);

	undo_redo->add_do_method(this, "update_custom_types");
	undo_redo->add_undo_method(this, "update_custom_types");

	undo_redo->add_do_method(this, "emit_signal", custom_type_changed);
	undo_redo->add_undo_method(this, "emit_signal", custom_type_changed);

	undo_redo->commit_action();
}

void EditorCustomTypeSettings::set_template_name(const String &p_name) {
	custom_type_add_name->set_text(p_name);
}

String EditorCustomTypeSettings::get_template_name() const {
	return custom_type_add_name->get_text();
}

void EditorCustomTypeSettings::set_template_path(const String &p_path) {
	custom_type_add_path->get_line_edit()->set_text(p_path);
}

String EditorCustomTypeSettings::get_template_path() const {
	return custom_type_add_path->get_line_edit()->get_text();
}

void EditorCustomTypeSettings::_bind_methods() {

	ClassDB::bind_method("_custom_type_add", &EditorCustomTypeSettings::_custom_type_add);
	ClassDB::bind_method("_custom_type_selected", &EditorCustomTypeSettings::_custom_type_selected);
	ClassDB::bind_method("_custom_type_edited", &EditorCustomTypeSettings::_custom_type_edited);
	ClassDB::bind_method("_custom_type_button_pressed", &EditorCustomTypeSettings::_custom_type_button_pressed);
	ClassDB::bind_method("_custom_type_file_callback", &EditorCustomTypeSettings::_custom_type_file_callback);
	ClassDB::bind_method("_custom_type_activated", &EditorCustomTypeSettings::_custom_type_activated);
	ClassDB::bind_method("_custom_type_open", &EditorCustomTypeSettings::_custom_type_open);

	ClassDB::bind_method("update_custom_types", &EditorCustomTypeSettings::update_custom_types);
	ClassDB::bind_method("custom_type_add", &EditorCustomTypeSettings::custom_type_add);
	ClassDB::bind_method("custom_type_remove", &EditorCustomTypeSettings::custom_type_remove);

	ADD_SIGNAL(MethodInfo("custom_type_changed"));
}

EditorCustomTypeSettings::EditorCustomTypeSettings() {

	// Make first cache
	Dictionary custom_types_dict;
	if (ProjectSettings::get_singleton()->has_setting(property_name))
		custom_types_dict = ProjectSettings::get_singleton()->get(property_name);

	List<Variant> names;
	custom_types_dict.get_key_list(&names);

	for (List<Variant>::Element *E = names.front(); E; E = E->next()) {

		StringName name = E->get();
		Dictionary data = custom_types_dict[name];

		if (name == StringName())
			continue;

		String path = data["path"];

		custom_types[name] = CustomTypeInfo(name, path);
		path_map[path] = name;
	}

	custom_type_changed = "custom_type_changed";
	property_name = "custom_types";

	updating_custom_type = false;
	selected_custom_type = "";

	HBoxContainer *hbc = memnew(HBoxContainer);
	add_child(hbc);

	Label *l = memnew(Label);
	l->set_text(TTR("Name:"));
	hbc->add_child(l);

	custom_type_add_name = memnew(LineEdit);
	custom_type_add_name->set_h_size_flags(SIZE_EXPAND_FILL);
	hbc->add_child(custom_type_add_name);

	l = memnew(Label);
	l->set_text(TTR("Path:"));
	hbc->add_child(l);

	custom_type_add_path = memnew(EditorLineEditFileChooser);
	custom_type_add_path->set_h_size_flags(SIZE_EXPAND_FILL);
	custom_type_add_path->get_file_dialog()->set_mode(EditorFileDialog::MODE_OPEN_FILE);
	custom_type_add_path->get_file_dialog()->connect("file_selected", this, "_custom_type_file_callback");
	hbc->add_child(custom_type_add_path);

	Button *add_custom_type = memnew(Button);
	add_custom_type->set_text(TTR("Add"));
	add_custom_type->connect("pressed", this, "_custom_type_add");
	hbc->add_child(add_custom_type);

	tree = memnew(Tree);
	tree->set_hide_root(true);
	tree->set_select_mode(Tree::SELECT_MULTI);
	tree->set_allow_reselect(true);

	tree->set_drag_forwarding(this);

	tree->set_columns(4);
	tree->set_column_titles_visible(true);

	tree->set_column_title(0, TTR("Name"));
	tree->set_column_expand(0, true);
	tree->set_column_min_width(0, 100);

	tree->set_column_title(1, TTR("Type"));
	tree->set_column_expand(1, true);
	tree->set_column_min_width(1, 100);

	tree->set_column_title(2, TTR("Path"));
	tree->set_column_expand(2, true);
	tree->set_column_min_width(2, 100);

	tree->set_column_expand(3, false);
	tree->set_column_min_width(3, 120 * EDSCALE);

	tree->connect("cell_selected", this, "_custom_type_selected");
	tree->connect("item_edited", this, "_custom_type_edited");
	tree->connect("button_pressed", this, "_custom_type_button_pressed");
	tree->connect("item_activated", this, "_custom_type_activated");
	tree->set_v_size_flags(SIZE_EXPAND_FILL);

	add_child(tree, true);
}

EditorCustomTypeSettings::~EditorCustomTypeSettings() {
}

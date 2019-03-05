/*************************************************************************/
/*  editor_custom_type_settings.h                                     */
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

#ifndef EDITOR_CUSTOM_TYPE_SETTINGS_H
#define EDITOR_CUSTOM_TYPE_SETTINGS_H

#include "editor_file_dialog.h"
#include "scene/gui/tree.h"

class EditorCustomTypeSettings : public VBoxContainer {

	GDCLASS(EditorCustomTypeSettings, VBoxContainer);

	enum {
		BUTTON_OPEN,
		BUTTON_DELETE
	};

	String custom_type_changed;
	String property_name;

	struct CustomTypeInfo {
		StringName name;
		String path;

		CustomTypeInfo(const StringName &p_name = "", const String &p_path = "") {
			name = p_name;
			path = p_path;
		}
	};

	HashMap<StringName, CustomTypeInfo> custom_types;
	HashMap<String, StringName> path_map;
	bool updating_custom_type;
	int number_of_custom_types;
	String selected_custom_type;

	Tree *tree;
	EditorLineEditFileChooser *custom_type_add_path;
	LineEdit *custom_type_add_name;

	bool _custom_type_name_is_valid(const String &p_name, String *r_error = NULL);

	void _update_tree();

	void _custom_type_add();
	void _custom_type_selected();
	void _custom_type_edited();
	void _custom_type_button_pressed(Object *p_item, int p_column, int p_button);
	void _custom_type_activated();
	void _custom_type_open(const String &fpath);
	void _custom_type_file_callback(const String &p_path);
	Object *_create_custom_type(const String &p_path);

protected:
	void _notification(int p_what);
	static void _bind_methods();

public:
	void update_custom_types();
	void custom_type_add(const String &p_name, const String &p_path, const String &p_icon_path = "");
	void custom_type_remove(const String &p_name);

	void set_template_name(const String &p_name);
	String get_template_name() const;
	void set_template_path(const String &p_path);
	String get_template_path() const;
	LineEdit *get_name_line_edit() { return custom_type_add_name; }
	LineEdit *get_path_line_edit() { return custom_type_add_path->get_line_edit(); }

	void get_custom_type_list(List<StringName> *p_list) const { custom_types.get_key_list(p_list); }
	bool custom_type_exists(const StringName &p_name) const { return custom_types.has(p_name); }
	StringName custom_type_get_name_by_path(const String &p_path) const { return path_map.has(p_path) ? path_map[p_path] : StringName(); }
	String custom_type_get_path(const StringName &p_name) const { return custom_types.has(p_name) ? custom_types[p_name].path : String(); }
	StringName custom_type_get_base(const StringName &p_name) const;
	StringName custom_type_get_base_file(const String &p_path) const;
	StringName custom_type_get_name(const String &p_path) const;
	Object *custom_type_instance(const StringName &p_name);
	bool custom_type_is_parent(const StringName &p_name, const StringName &p_inherits);

	EditorCustomTypeSettings();
	~EditorCustomTypeSettings();
};

#endif // EDITOR_CUSTOM_TYPE_SETTINGS_H

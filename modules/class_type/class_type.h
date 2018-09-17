/*************************************************************************/
/*  class_type.h                                                         */
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

#ifndef CLASS_TYPE_H
#define CLASS_TYPE_H

#include "core/array.h"
#include "core/reference.h"
#include "core/resource.h"

class ClassType : public Reference {
	GDCLASS(ClassType, Reference);

	StringName _name;
	String _path;

protected:
	static void _bind_methods();

	void _update_path_by_name();
	Array _get_class_list();

public:
	static void get_class_list(List<StringName> *p_list);
	static StringName get_name_by_path(const String &p_path);
	static StringName get_name_by_object(const Object *p_object, String *r_path = NULL);
	static bool is_valid_path(const String &p_path);
	static RES get_scene_root_script(const String &p_path);
	static RES get_scene_root_scene(const String &p_path);

	void set_name(const String &p_name);
	String get_name() const;
	void set_path(const String &p_path);
	String get_path() const;
	bool has_valid_path() const { return is_valid_path(_path); }

	bool is_engine_class() const;
	bool is_script_class() const;
	bool is_scene_template() const;
	bool exists() const;

	bool is_non_class_res() const;

	RES get_res() const;
	RES get_editor_icon() const;

	StringName get_engine_parent() const;
	StringName get_script_parent() const;
	StringName get_scene_parent() const;
	StringName get_parent_class() const;
	Array get_parents() const;

	bool is_engine_parent(const StringName &p_class) const;
	bool is_script_parent(const StringName &p_class) const;
	bool is_scene_parent(const StringName &p_class) const;
	bool is_parent_class(const StringName &p_class) const;

	bool can_instance() const;
	Object *instance() const;

	static Ref<ClassType> from_name(const StringName &p_name);
	static Ref<ClassType> from_path(const String &p_path);
	static Ref<ClassType> from_object(const Object *p_object);
	ClassType();
};

#endif

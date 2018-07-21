/*************************************************************************/
/*  data_graph.cpp                                                       */
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

#include "core/class_db.h"
#include "data_graph.h"

void DataGraphVertex::_add_tags(Array p_tags) {
	for (int i = 0; i < p_tags.size(); i++) {
		Variant v = p_tags[i];
		if (v.get_type() != Variant::STRING)
			return;
		tags.insert(v);
	}
}

void DataGraphVertex::_remove_tags(Array p_tags) {
	for (int i = 0; i < p_tags.size(); i++) {
		Variant v = p_tags[i];
		if (v.get_type() != Variant::STRING)
			return;
		tags.erase(v);
	}
}

bool DataGraphVertex::_has_tags(Array p_tags) const {
	bool result = true;
	for (int i = 0; i < p_tags.size(); i++) {
		Variant v = p_tags[i];
		if (v.get_type() != Variant::STRING)
			return false;
		result &= tags.has(v);
	}
	return result;
}

Array DataGraphVertex::_get_tags() const {
	Array ret;
	for (const Set<StringName>::Element *E = tags.front(); E; E = E->next()) {
		ret.append(E->get());
	}
	return ret;
}

void DataGraphVertex::set_data(Variant p_data) {
	_data = p_data;
}

Variant DataGraphVertex::get_data() const {
	return _data;
}

void DataGraphVertex::set_graph(DataGraph *p_graph) {
	_graph = p_graph;
}

DataGraph *DataGraphVertex::get_graph() {
	return _graph;
}

void DataGraphVertex::add_tags(const List<StringName> &p_tags) {
	ERR_FAIL_COND(!_graph);
	for (const List<StringName>::Element *E = p_tags.front(); E; E = E->next()) {
		if (_graph->)
		tags.insert(E->get());
	}
}

void DataGraphVertex::remove_tags(const List<StringName> &p_tags) {
	ERR_FAIL_COND(!_graph);
	return _graph->v_remove_tags(this, p_tags);
}

bool DataGraphVertex::has_tags(const List<StringName> &p_tags) {
	ERR_FAIL_COND(!_graph);
	return _graph->v_has_tags(this, p_tags);
}

const Set<StringName> &DataGraphVertex::get_tags() {
	ERR_FAIL_COND(!_graph);
	return _graph->v_get_tags(this);
}

void DataGraphVertex::clear_tags() {
	ERR_FAIL_COND(!_graph);
	_graph->v_clear_tags(this);
}

void DataGraphVertex::_bind_methods() {

	ClassDB::bind_method(D_METHOD("set_data"), &DataGraphVertex::set_data);
	ClassDB::bind_method(D_METHOD("get_data"), &DataGraphVertex::get_data);

	ClassDB::bind_method(D_METHOD("add_tags"), &DataGraphVertex::_add_tags);
	ClassDB::bind_method(D_METHOD("remove_tags"), &DataGraphVertex::_remove_tags);
	ClassDB::bind_method(D_METHOD("has_tags"), &DataGraphVertex::_has_tags);
	ClassDB::bind_method(D_METHOD("get_tags"), &DataGraphVertex::_get_tags);
	ClassDB::bind_method(D_METHOD("clear_tags"), &DataGraphVertex::clear_tags);

	ADD_PROPERTY(PropertyInfo(Variant::NIL, "metadata"), "set_metadata", "get_metadata");
}

DataGraphVertex::DataGraphVertex() {

}

DataGraphVertex::~DataGraphVertex() {

}

void DataGraph::_add_vertex(Object *p_vertex) {

}

void DataGraph::_remove_vertex(Object *p_vertex) {

}

void DataGraph::add_vertex(DataGraphVertex *p_vertex) {

}

void DataGraph::remove_vertex(DataGraphVertex *p_vertex) {

	//TODO: cleanup connections

	verts_in.erase(p_vertex);
	verts_out.erase(p_vertex);

	List<StringName> keys;
	tag_index.get_key_list(&keys);
	for (List<StringName>::Element *E = keys.front(); E; E = E->next()) {
		tag_index[E->get()].erase(p_vertex);
	}

	if (!p_vertex->get_script().is_null()) {
		script_index[p_vertex->get_script()].erase(p_vertex);
	}
}

void DataGraph::v_add_tags(DataGraphVertex *p_vertex, const List<StringName> &p_tags) {
	for (const List<StringName>::Element *E = p_tags.front(); E; E = E->next()) {
		tag_index[E->get()].insert(p_vertex);
	}
}

void DataGraph::v_remove_tags(DataGraphVertex *p_vertex, const List<StringName> &p_tags) {
	for (const List<StringName>::Element *E = p_tags.front(); E; E = E->next()) {
		tag_index[E->get()].erase(p_vertex);
	}
}

bool DataGraph::v_has_tags(DataGraphVertex *p_vertex, const List<StringName> &p_tags) const {
	bool ret = true;
	List<StringName> keys;
	tag_index.get_key_list(&keys);
	for (List<StringName>::Element *E = keys.front(); E && ret; E = E->next()) {
		ret &= tag_index[E->get()].has(p_vertex);
	}
	return ret;
}

const Set<StringName> &DataGraph::v_get_tags(DataGraphVertex *p_vertex) const {
	Set<StringName> ret;
	List<StringName> keys;
	tag_index.get_key_list(&keys);
	for (List<StringName>::Element *E = keys.front(); E; E = E->next()) {
		if (tag_index[E->get()].has(p_vertex))
			ret.insert(E->get());
	}
	return ret;
}

void DataGraph::v_clear_tags(DataGraphVertex *p_vertex) {
	List<StringName> keys;
	tag_index.get_key_list(&keys);
	for (List<StringName>::Element *E = keys.front(); E; E = E->next()) {
		tag_index[E->get()].erase(p_vertex);
	}
}


void DataGraph::clear() {
	tag_index.clear();
	script_index.clear();

	List<DataGraphVertex *> keys;
	verts_in.get_key_list(&keys);
	for (List<DataGraphVertex *>::Element *E = keys.front(); E; E = E->next()) {
		memdelete(E->get());
	}
	verts_out.clear();
}

void DataGraph::_bind_methods() {

}

DataGraph::DataGraph() {

}

DataGraph::~DataGraph() {

}

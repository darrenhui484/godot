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

void DataGraphVertex::set_metadata(Variant p_metadata) {
	_metadata = p_metadata;
}

Variant DataGraphVertex::get_metadata() const {
	return _metadata;
}

void DataGraphVertex::add_tags(const List<StringName> &p_tags) {
	for (const List<StringName>::Element *E = p_tags.front(); E; E = E->next()) {
		tags.insert(E->get());
	}
}

void DataGraphVertex::remove_tags(const List<StringName> &p_tags) {
	for (const List<StringName>::Element *E = p_tags.front(); E; E = E->next()) {
		tags.erase(E->get());
	}
}

bool DataGraphVertex::has_tags(const List<StringName> &p_tags) const {
	bool result = true;
	for (const List<StringName>::Element *E = p_tags.front(); E && result; E = E->next()) {
		result &= tags.has(E->get());
	}
	return result;
}

const Set<StringName> &DataGraphVertex::get_tags() const {
	return tags;
}

void DataGraphVertex::clear_tags() {
	tags.clear();
}

void DataGraphVertex::_bind_methods() {

	ClassDB::bind_method(D_METHOD("set_metadata"), &DataGraphVertex::set_metadata);
	ClassDB::bind_method(D_METHOD("get_metadata"), &DataGraphVertex::get_metadata);

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

void DataGraphLayer::_bind_methods() {

}

DataGraphLayer::DataGraphLayer() {

}

DataGraphLayer::~DataGraphLayer() {

}

DataGraphLayerVertexTags::DataGraphLayerVertexTags() {

}

DataGraphLayerVertexTags::~DataGraphLayerVertexTags() {

}

void DataGraph::_bind_methods() {

}

DataGraph::DataGraph() {

}

DataGraph::~DataGraph() {
	for (int i = 0; i < layers.size(); i++) {
		memdelete(layers[i]);
	}
}

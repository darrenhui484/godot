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

#include "data_graph.h"

struct DataGraphInterface {

	void add_vertex(List<String> *p_labels, const Variant &p_metadata = Variant()) = 0;

	virtual ~DataGraphInterface() = 0;
};

struct DataGraphImplementationList : public DataGraphInterface {

	struct VertexCluster {
		DataGraphVertex vertex;
		List<DataGraphEdge> edges;
	};

	Vector<VertexCluster> vertex_array;

	void add_vertex(List<String> *p_labels, const Variant &p_metadata = Variant());

};

struct DataGraphImplementationMatrix : public DataGraphInterface {

	Vector<DataGraphVertex> vertices;
	Vector<Vector<DataGraphEdge*>> edges;

	void add_vertex(List<String> *p_labels, const Variant &p_metadata = Variant());
};

void DataGraphVertex::get_label_list(List<String> *p_list) const {

	for (Set<String>::Element *E = labels.front(); E; E = E->next()) {
		p_list->push_back(E->get());
	}
}

PoolStringArray DataGraphVertex::get_labels() const {

	PoolStringArray ret;

	for (Set<String>::Element *E = labels.front(); E; E = E->next()) {
		ret.push_back(E->get());
	}

	return ret;
}

void DataGraphVertex::_bind_methods() {

	ClassDB::bind_method(D_METHOD("get_labels"), &DataGraphVertex::get_labels);
	ClassDB::bind_method(D_METHOD("add_label", "p_label"), &DataGraphVertex::add_label);
	ClassDB::bind_method(D_METHOD("remove_label", "p_label"), &DataGraphVertex::remove_label);
	ClassDB::bind_method(D_METHOD("has_label", "p_label"), &DataGraphVertex::has_label);
	ClassDB::bind_method(D_METHOD("clear_labels"), &DataGraphVertex::clear_labels);
	ClassDB::bind_method(D_METHOD("set_metadata", "p_metadata"), &DataGraphVertex::set_metadata);
	ClassDB::bind_method(D_METHOD("get_metadata", "p_metadata"), &DataGraphVertex::get_metadata);

	ADD_PROPERTY(PropertyInfo(Variant::NIL, "metadata"), "set_metadata", "get_metadata");
}

const DataGraphVertex *DataGraphEdge::get_start_vertex() const {
	ERR_FAIL_COND_V(!graph, NULL);
	ERR_FAIL_COND_V(graph->vertex_array.size() >= start, NULL);
	return graph->vertex_array[start].vertex;
}

const DataGraphVertex *DataGraphEdge::get_end_vertex() const {
	ERR_FAIL_COND_V(!graph, NULL);
	ERR_FAIL_COND_V(graph->vertex_array.size() >= end, NULL);
	return graph->vertex_array[end].vertex;
}

void DataGraphEdge::_bind_methods() {

	ClassDB::bind_method(D_METHOD("get_start"), &DataGraphEdge::get_start_vertex);
	ClassDB::bind_method(D_METHOD("get_end"), &DataGraphEdge::get_end_vertex);
	ClassDB::bind_method(D_METHOD("get_label"), &DataGraphEdge::get_label);
	ClassDB::bind_method(D_METHOD("set_metadata", "p_metadata"), &DataGraphEdge::set_metadata);
	ClassDB::bind_method(D_METHOD("get_metadata", "p_metadata"), &DataGraphEdge::get_metadata);

	ADD_PROPERTY(PropertyInfo(Variant::NIL, "metadata"), "set_metadata", "get_metadata");
}

DataGraphEdge::DataGraphEdge(uint32_t p_start, uint32_t p_end, const String &p_label, const Variant &p_metadata = Variant())
	: start(p_start), end(p_end), label(p_label), metadata(p_metadata) {

}

DataGraphEdge::~DataGraphEdge() {

}

void DataGraph::_bind_methods() {

}

DataGraph::DataGraph() {

}

DataGraph::~DataGraph() {

}


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

void DataGraphVertex::get_label_list(List<StringName> *p_list) const {
	for (const List<StringName>::Element *E = _labels.front(); E; E = E->next()) {
		p_list->push_back(E->get());
	}
}

PoolStringArray DataGraphVertex::get_labels() const {

	PoolStringArray ret;

	for (const List<StringName>::Element *E = _labels.front(); E; E = E->next()) {
		ret.push_back(Variant(E->get()));
	}

	return ret;
}

void DataGraphVertex::add_label(const StringName &p_label) {
	_labels.push_back(p_label);
}

void DataGraphVertex::remove_label(const StringName &p_label) {
	_labels.erase(p_label);
}

bool DataGraphVertex::has_label(const StringName &p_label) {
	return _labels.find(p_label)->get() != StringName();
}

void DataGraphVertex::clear_labels() {
	_labels.clear();
}

Dictionary DataGraphVertex::get_meta() const {
	return _meta;
}

void DataGraphVertex::set_meta(Dictionary p_meta) {
	_meta = p_meta;
}

void DataGraphVertex::_bind_methods() {

	ClassDB::bind_method(D_METHOD("get_labels"), &DataGraphVertex::get_labels);
	ClassDB::bind_method(D_METHOD("add_label", "p_label"), &DataGraphVertex::add_label);
	ClassDB::bind_method(D_METHOD("remove_label", "p_label"), &DataGraphVertex::remove_label);
	ClassDB::bind_method(D_METHOD("has_label", "p_label"), &DataGraphVertex::has_label);
	ClassDB::bind_method(D_METHOD("clear_labels"), &DataGraphVertex::clear_labels);
	ClassDB::bind_method(D_METHOD("set_meta", "p_meta_dict"), &DataGraphVertex::set_meta);
	ClassDB::bind_method(D_METHOD("get_meta"), &DataGraphVertex::get_meta);

	ADD_PROPERTY(PropertyInfo(Variant::NIL, "meta"), "set_meta", "get_meta");
}

const DataGraphVertex *DataGraphEdge::get_start_vertex() const {
	ERR_FAIL_COND_V(!_graph, NULL);
	return _graph->get_vertex(_start);
}

const DataGraphVertex *DataGraphEdge::get_end_vertex() const {
	ERR_FAIL_COND_V(!_graph, NULL);
	return _graph->get_vertex(_end);
}

Dictionary DataGraphEdge::get_meta() const {
	return _meta;
}

void DataGraphEdge::set_meta(Dictionary p_meta) {
	_meta = p_meta;
}

void DataGraphEdge::_bind_methods() {

	ClassDB::bind_method(D_METHOD("get_start"), &DataGraphEdge::get_start_vertex);
	ClassDB::bind_method(D_METHOD("get_end"), &DataGraphEdge::get_end_vertex);
	ClassDB::bind_method(D_METHOD("get_label"), &DataGraphEdge::get_label);
	ClassDB::bind_method(D_METHOD("set_meta", "p_meta_dict"), &DataGraphEdge::set_meta);
	ClassDB::bind_method(D_METHOD("get_meta"), &DataGraphEdge::get_meta);

	ADD_PROPERTY(PropertyInfo(Variant::NIL, "meta"), "set_meta", "get_meta");
}

DataGraphEdge::DataGraphEdge(eid p_eid, vid p_start, vid p_end, const StringName &p_label, Dictionary p_meta)
	: _id(p_eid), _start(p_start), _end(p_end), _label(p_label), _meta(p_meta) {

}

DataGraphEdge::~DataGraphEdge() {

}

DataGraph::VertexCluster *DataGraph::get_cluster(vid p_vid) {
	return &_vertices[p_vid];
}

DataGraphVertex *DataGraph::get_vertex(vid p_vid) {
	return &get_cluster(p_vid)->vertex;
}

void DataGraph::get_vertex_list(List<DataGraphVertex*> *p_vertices) {
	for (int i = 0; i < _vertices.size(); ++i) {
		p_vertices->push_back(&_vertices[i].vertex);
	}
}

Array DataGraph::get_vertices() {
	Array ret;

	for (int i = 0; i < _vertices.size(); ++i) {
		ret.push_back(Variant(&_vertices[i].vertex));
	}

	return ret;
}

void DataGraph::add_vertex(List<StringName> *p_labels, Dictionary p_meta) {
	if (_free_vids.empty()) {
		_vertices.push_back(VertexCluster(_vertices.size(), p_labels, p_meta));
	} else {
		vid id = _free_vids[_free_vids.size() - 1];
		_free_vids.resize(_free_vids.size() - 1);

		_vertices[id].vertex._id = id;
		_vertices[id].vertex._labels = *p_labels;
		_vertices[id].vertex._meta = p_meta;
	}
}

void DataGraph::add_vertex_array(Array p_labels, Dictionary p_meta) {
	List<StringName> labels;
	for (int i = 0; i < p_labels.size(); ++i) {
		labels.push_back(StringName(p_labels[i]));
	}
	add_vertex(&labels, p_meta);
}

void DataGraph::remove_vertex(vid p_vid) {
	if (p_vid >= _vertices.size() || _free_vids.find(p_vid) != -1) {
		WARN_PRINT(("Failed to remove non-existent vertex from DataGraph: " + itos(p_vid)).utf8().ptr());
		return;
	}
	_vertices[p_vid].vertex._id = -1;
	_free_vids.push_back(p_vid);
	for (List<DataGraphEdge*>::Element *E = _vertices[p_vid].out_edges.front(); E; E = E->next()) {
		remove_edge(E->get()->_id);
	}
	for (List<DataGraphEdge*>::Element *E = _vertices[p_vid].in_edges.front(); E; E = E->next()) {
		remove_edge(E->get()->_id);
	}
	for (List<StringName>::Element *E = _vertices[p_vid].vertex._labels.front(); E; E = E->next()) {
		_vertex_map[E->get()].erase(&_vertices[p_vid].vertex);
	}
}

size_t DataGraph::get_num_vertices() {
	return _vertices.size() - _free_vids.size();
}

bool DataGraph::has_vertex(vid p_vid) {
	return p_vid < _vertices.size() && _free_vids.find(p_vid) == -1;
}

DataGraphEdge *DataGraph::get_edge(vid p_start, vid p_end) {
	DataGraph::VertexCluster *cluster = get_cluster(p_start);
	for (List<DataGraphEdge*>::Element *E = cluster->out_edges.front(); E; E = E->next()) {
		if (E->get()->get_end() == p_end) {
			return E->get();
		}
	}
	return NULL;
}

DataGraphEdge *DataGraph::get_edge_id(eid p_eid) {
	return &_edges[p_eid];
}

void DataGraph::get_edge_list(List<DataGraphEdge*> *p_edges) {
	for (int i = 0; i < _edges.size(); ++i) {
		p_edges->push_back(&_edges[i]);
	}
}

Array DataGraph::get_edges() {
	Array ret;

	for (int i = 0; i < _edges.size(); ++i) {
		ret.push_back(Variant(&_edges[i]));
	}

	return ret;
}

Error DataGraph::add_edge(vid p_start, vid p_end, const StringName &p_label, Dictionary p_meta) {
	if (p_start >= _edges.size() || _free_vids.find(p_start) != -1) {
		WARN_PRINT(("Failed to locate non-existent vertex in DataGraph: " + itos(p_start)).utf8().ptr());
		return ERR_DOES_NOT_EXIST;
	}
	if (p_end >= _edges.size() || _free_vids.find(p_end) != -1) {
		WARN_PRINT(("Failed to locate non-existent vertex in DataGraph: " + itos(p_end)).utf8().ptr());
		return ERR_DOES_NOT_EXIST;
	}

	if (_free_eids.empty()) {
		_edges.push_back(DataGraphEdge(_edges.size(), p_start, p_end, p_label, p_meta));
	} else {
		eid id = _free_eids[_free_eids.size() - 1];
		_free_eids.resize(_free_eids.size() - 1);

		_edges[id]._id = id;
		_edges[id]._label = p_label;
		_edges[id]._meta = p_meta;
	}

	return OK;
}

Error DataGraph::remove_edge(eid p_eid) {
	if (p_eid >= _edges.size() || _free_eids.find(p_eid) != -1) {
		WARN_PRINT(("Failed to remove non-existent edge from DataGraph: " + itos(p_eid)).utf8().ptr());
		return ERR_DOES_NOT_EXIST;
	}
	_edges[p_eid]._id = -1;
	_free_eids.push_back(p_eid);
	_edge_map[_edges[p_eid]._label].erase(&_edges[p_eid]);

	return OK;
}

size_t DataGraph::get_num_edges() {
	return _edges.size() - _free_eids.size();
}

bool DataGraph::has_edge(eid p_eid) {
	return p_eid < _edges.size() && _free_eids.find(p_eid) == -1;
}

void DataGraph::get_edges_to_vertex(vid p_vid, List<DataGraphEdge*> *p_edges) {
	const DataGraph::VertexCluster *cluster = get_cluster(p_vid);
	for (const List<DataGraphEdge*>::Element *E = cluster->in_edges.front(); E; E = E->next()) {
		p_edges->push_back(E->get());
	}
}

Array DataGraph::get_edges_to_vertex_array(vid p_vid) {
	Array ret;
	const DataGraph::VertexCluster *cluster = get_cluster(p_vid);
	for (const List<DataGraphEdge*>::Element *E = cluster->in_edges.front(); E; E = E->next()) {
		ret.push_back(Variant(E->get()));
	}

	return ret;
}

void DataGraph::get_edges_from_vertex(vid p_vid, List<DataGraphEdge*> *p_edges) {
	const DataGraph::VertexCluster *cluster = get_cluster(p_vid);
	for (const List<DataGraphEdge*>::Element *E = cluster->out_edges.front(); E; E = E->next()) {
		p_edges->push_back(E->get());
	}
}

Array DataGraph::get_edges_from_vertex_array(vid p_vid) {
	Array ret;
	const DataGraph::VertexCluster *cluster = get_cluster(p_vid);
	for (const List<DataGraphEdge*>::Element *E = cluster->out_edges.front(); E; E = E->next()) {
		ret.push_back(Variant(E->get()));
	}

	return ret;
}

void DataGraph::get_vertices_with_label_list(const StringName &p_label, List<DataGraphVertex*> *p_vertices) {

	for (List<DataGraphVertex*>::Element *E = _vertex_map[p_label].front(); E; E = E->next()) {
		p_vertices->push_back(E->get());
	}
}

Array DataGraph::get_vertices_with_label_array(const StringName &p_label) {

	Array ret;

	for (List<DataGraphVertex*>::Element *E = _vertex_map[p_label].front(); E; E = E->next()) {
		ret.push_back(Variant(E->get()));
	}

	return ret;
}

void DataGraph::get_edges_with_label_list(const StringName &p_label, List<DataGraphEdge*> *p_edges) {

	for (List<DataGraphEdge*>::Element *E = _edge_map[p_label].front(); E; E = E->next()) {
		p_edges->push_back(E->get());
	}
}

Array DataGraph::get_edges_with_label_array(const StringName &p_label) {

	Array ret;

	for (List<DataGraphEdge*>::Element *E = _edge_map[p_label].front(); E; E = E->next()) {
		ret.push_back(Variant(E->get()));
	}

	return ret;
}

void DataGraph::get_vertex_label_list(List<StringName> *p_labels) {
	_vertex_map.get_key_list(p_labels);
}

Array DataGraph::get_vertex_label_array() {

	Array ret;
	List<StringName> keys;
	_vertex_map.get_key_list(&keys);

	for (List<StringName>::Element *E = keys.front(); E; E = E->next()) {
		ret.push_back(Variant(E->get()));
	}

	return ret;
}

void DataGraph::get_edge_label_list(List<StringName> *p_labels) {
	_edge_map.get_key_list(p_labels);
}

Array DataGraph::get_edge_label_array() {

	Array ret;
	List<StringName> keys;
	_edge_map.get_key_list(&keys);

	for (List<StringName>::Element *E = keys.front(); E; E = E->next()) {
		ret.push_back(Variant(E->get()));
	}

	return ret;
}

void DataGraph::clear() {
	_vertices.clear();
	_edges.clear();
	_vertex_map.clear();
	_edge_map.clear();
}

void DataGraph::_bind_methods() {

	ClassDB::bind_method(D_METHOD("get_vertex", "p_vertex_id"), &DataGraph::get_vertex);
	ClassDB::bind_method(D_METHOD("get_vertices"), &DataGraph::get_vertices);
	ClassDB::bind_method(D_METHOD("get_edge", "p_edge_id"), &DataGraph::get_edge);
	ClassDB::bind_method(D_METHOD("get_label"), &DataGraph::get_label);
	ClassDB::bind_method(D_METHOD("set_meta", "p_meta_dict"), &DataGraph::set_meta);
	ClassDB::bind_method(D_METHOD("get_meta"), &DataGraph::get_meta);

	ADD_PROPERTY(PropertyInfo(Variant::NIL, "meta"), "set_meta", "get_meta");
}

DataGraph::DataGraph() {

}

DataGraph::~DataGraph() {

}


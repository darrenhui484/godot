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
#include "core/io/marshalls.h"

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
	return _labels.empty() ? false : _labels.find(p_label)->get() != StringName();
}

void DataGraphVertex::clear_labels() {
	_labels.clear();
}

Dictionary DataGraphVertex::get_metadata() const {
	return _metadata;
}

void DataGraphVertex::set_metadata(Dictionary p_metadata) {
	_metadata = p_metadata;
}

List<DataGraphEdge*> DataGraphVertex::get_in_edges() {
	return _graph->get_vertex_cluster(_id)->get_in_edges();
}

Array DataGraphVertex::get_in_edges_array() {
	Array ret;

	for (List<DataGraphEdge*>::Element *E = _graph->get_vertex_cluster(_id)->get_in_edges().front(); E; E = E->next()) {
		ret.push_back(Variant(E->get()));
	}

	return ret;
}

List<DataGraphEdge*> DataGraphVertex::get_out_edges() {
	return _graph->get_vertex_cluster(_id)->get_out_edges();
}

Array DataGraphVertex::get_out_edges_array() {
	Array ret;

	for (List<DataGraphEdge*>::Element *E = _graph->get_vertex_cluster(_id)->get_out_edges().front(); E; E = E->next()) {
		ret.push_back(Variant(E->get()));
	}

	return ret;
}

void DataGraphVertex::_bind_methods() {

	ClassDB::bind_method(D_METHOD("get_labels"), &DataGraphVertex::get_labels);
	ClassDB::bind_method(D_METHOD("add_label", "p_label"), &DataGraphVertex::add_label);
	ClassDB::bind_method(D_METHOD("remove_label", "p_label"), &DataGraphVertex::remove_label);
	ClassDB::bind_method(D_METHOD("has_label", "p_label"), &DataGraphVertex::has_label);
	ClassDB::bind_method(D_METHOD("clear_labels"), &DataGraphVertex::clear_labels);

	ClassDB::bind_method(D_METHOD("set_metadata", "p_metadata_dict"), &DataGraphVertex::set_metadata);
	ClassDB::bind_method(D_METHOD("get_metadata"), &DataGraphVertex::get_metadata);

	ClassDB::bind_method(D_METHOD("get_in_edges"), &DataGraphVertex::get_in_edges_array);
	ClassDB::bind_method(D_METHOD("get_out_edges"), &DataGraphVertex::get_out_edges_array);

	ADD_PROPERTY(PropertyInfo(Variant::NIL, "metadata"), "set_metadata", "get_metadata");
}

DataGraphVertex::DataGraphVertex(const DataGraphVertex &p_other) {
	_id = p_other._id;
	_labels.clear();
	p_other.get_label_list(&_labels);
	_metadata = p_other._metadata;
}

bool DataGraphVertex::operator<(DataGraphVertex &p_other) {
	return _id < p_other._id;
}

bool DataGraphVertex::operator==(DataGraphVertex &p_other) {
	return *this < p_other && p_other < *this;
}

const DataGraphVertex *DataGraphEdge::get_start_vertex() const {
	ERR_FAIL_COND_V(!_graph, NULL);
	return _graph->get_vertex(_start);
}

const DataGraphVertex *DataGraphEdge::get_end_vertex() const {
	ERR_FAIL_COND_V(!_graph, NULL);
	return _graph->get_vertex(_end);
}

Dictionary DataGraphEdge::get_metadata() const {
	return _metadata;
}

void DataGraphEdge::set_metadata(Dictionary p_metadata) {
	_metadata = p_metadata;
}

void DataGraphEdge::_bind_methods() {

	//ClassDB::bind_method(D_METHOD("get_start"), &DataGraphEdge::get_start_vertex);
	//ClassDB::bind_method(D_METHOD("get_end"), &DataGraphEdge::get_end_vertex);
	//ClassDB::bind_method(D_METHOD("get_label"), &DataGraphEdge::get_label);
	//ClassDB::bind_method(D_METHOD("set_metadata", "p_metadata_dict"), &DataGraphEdge::set_metadata);
	//ClassDB::bind_method(D_METHOD("get_metadata"), &DataGraphEdge::get_metadata);

	//ADD_PROPERTY(PropertyInfo(Variant::NIL, "metadata"), "set_metadata", "get_metadata");
}

DataGraphEdge::DataGraphEdge(eid p_eid, vid p_start, vid p_end, const StringName &p_label, Dictionary p_metadata)
	: _id(p_eid), _start(p_start), _end(p_end), _label(p_label), _metadata(p_metadata) {}

DataGraphEdge::DataGraphEdge(const DataGraphEdge &p_other) {
	_id = p_other._id;
	_start = p_other._start;
	_end = p_other._end;
	_label = p_other._label;
	_metadata = p_other._metadata;
	_graph = p_other._graph;
}

bool DataGraphEdge::operator<(DataGraphEdge &p_other) {
	return _id < p_other._id;
}

bool DataGraphEdge::operator==(DataGraphEdge &p_other) {
	return *this < p_other && p_other < *this;
}

DataGraph::VertexCluster::VertexCluster(vid p_vid, List<StringName> *p_labels, Dictionary p_metadata)
	: vertex(p_vid) {

	if (p_labels) {
		for (List<StringName>::Element *E = p_labels->front(); E; E = E->next()) {
			vertex.add_label(E->get());
		}
	}

	vertex.set_metadata(p_metadata);
}

DataGraph::VertexCluster::VertexCluster(const DataGraph::VertexCluster &p_other) {
	vertex = p_other.vertex;
	in_edges = p_other.in_edges;
	out_edges = p_other.out_edges;
}

bool DataGraph::VertexCluster::operator<(DataGraph::VertexCluster &p_other) {
	return vertex < p_other.vertex;
}

bool DataGraph::VertexCluster::operator==(DataGraph::VertexCluster &p_other) {
	return vertex == p_other.vertex;
}

DataGraphVertex *DataGraph::get_vertex(vid p_vid) {
	VertexCluster *cluster = (VertexCluster*) _vertices[p_vid].operator uint64_t();
	if (cluster) {
		return cluster->get_vertex();
	}
	return NULL;
}

DataGraph::VertexCluster *DataGraph::get_vertex_cluster(vid p_vid) {
	return (DataGraph::VertexCluster*) _vertices[p_vid].operator uint64_t();
}

void DataGraph::get_vertex_list(List<DataGraphVertex*> *p_vertices) {
	List<Variant> keys;
	_vertices.get_key_list(&keys);
	for (List<Variant>::Element *E = keys.front(); E; E = E->next()) {
		VertexCluster *cluster = (VertexCluster*) _vertices[E->get()].operator uint64_t();
		if (cluster) {
			p_vertices->push_back(cluster->get_vertex());
		}
	}
}

Array DataGraph::get_vertices() {
	Array ret;
	List<Variant> keys;
	_vertices.get_key_list(&keys);

	for (List<Variant>::Element *E = keys.front(); E; E = E->next()) {
		ret.push_back(E->get());
	}

	return ret;
}

DataGraphVertex *DataGraph::add_vertex(List<StringName> *p_labels, Dictionary p_metadata) {
	VertexCluster *cluster = memnew(VertexCluster(_vertices.size(), p_labels, p_metadata));
	_vertices[_vertices.size()] = cluster;
	return cluster->get_vertex();
}

DataGraphVertex *DataGraph::add_vertex_array(Array p_labels, Dictionary p_metadata) {
	List<StringName> labels;
	for (int i = 0; i < p_labels.size(); ++i) {
		labels.push_back(StringName(p_labels[i]));
	}
	return add_vertex(&labels, p_metadata);
}

void DataGraph::remove_vertex(vid p_vid) {
	if (!_vertices.has(p_vid)) {
		WARN_PRINT(("Failed to remove non-existent vertex from DataGraph: " + itos(p_vid)).utf8().ptr());
		return;
	}
	VertexCluster *cluster = get_vertex_cluster(p_vid);
	for (List<DataGraphEdge*>::Element *E = cluster->get_out_edges().front(); E; E = E->next()) {
		remove_edge(E->get()->_id);
	}
	for (List<DataGraphEdge*>::Element *E = cluster->get_in_edges().front(); E; E = E->next()) {
		remove_edge(E->get()->_id);
	}
	for (List<StringName>::Element *E = cluster->get_vertex()->_labels.front(); E; E = E->next()) {
		_vertex_map[E->get()].erase(cluster->get_vertex());
	}
	_vertices.erase(p_vid);
}

size_t DataGraph::get_num_vertices() {
	return _vertices.size();
}

bool DataGraph::has_vertex(vid p_vid) {
	return _vertices.has(p_vid);
}

DataGraphEdge *DataGraph::get_edge(vid p_start, vid p_end) {
	DataGraph::VertexCluster *cluster = get_vertex_cluster(p_start);
	for (List<DataGraphEdge*>::Element *E = cluster->get_out_edges().front(); E; E = E->next()) {
		if (E->get()->get_end() == p_end) {
			return E->get();
		}
	}
	return NULL;
}

DataGraphEdge *DataGraph::get_edge_id(eid p_eid) {
	return get_edge_id(p_eid);
}

void DataGraph::get_edge_list(List<DataGraphEdge*> *p_edges) {
	for (int i = 0; i < _edges.size(); ++i) {
		p_edges->push_back(get_edge_id(i));
	}
}

Array DataGraph::get_edges() {
	Array ret;

	for (int i = 0; i < _edges.size(); ++i) {
		ret.push_back(Variant(_edges[i]));
	}

	return ret;
}

eid DataGraph::add_edge(vid p_start, vid p_end, const StringName &p_label, Dictionary p_metadata) {
	if (!_vertices.has(p_start)) {
		WARN_PRINT(("Failed to locate non-existent vertex in DataGraph: " + itos(p_start)).utf8().ptr());
		return -1;
	}
	if (!_vertices.has(p_end)) {
		WARN_PRINT(("Failed to locate non-existent vertex in DataGraph: " + itos(p_end)).utf8().ptr());
		return -1;
	}

	DataGraphEdge *edge = memnew(DataGraphEdge(_edges.size(), p_start, p_end, p_label, p_metadata));
	_edges[_edges.size()] = edge;
}

Error DataGraph::remove_edge(eid p_eid) {
	if (!_edges.has(p_eid)) {
		WARN_PRINT(("Failed to remove non-existent edge from DataGraph: " + itos(p_eid)).utf8().ptr());
		return ERR_DOES_NOT_EXIST;
	}
	DataGraphEdge *edge = (DataGraphEdge*)(_edges[p_eid].operator uint64_t());
	_edge_map[edge->_label].erase(edge);
	_edges.erase(edge);

	return OK;
}

size_t DataGraph::get_num_edges() {
	return _edges.size();
}

bool DataGraph::has_edge(eid p_eid) {
	return _edges.has(p_eid);
}

void DataGraph::get_edges_to_vertex(vid p_vid, List<DataGraphEdge*> *p_edges) {
	DataGraph::VertexCluster *cluster = get_vertex_cluster(p_vid);
	for (const List<DataGraphEdge*>::Element *E = cluster->get_in_edges().front(); E; E = E->next()) {
		p_edges->push_back(E->get());
	}
}

Array DataGraph::get_edges_to_vertex_array(vid p_vid) {
	Array ret;
	DataGraph::VertexCluster *cluster = get_vertex_cluster(p_vid);
	for (const List<DataGraphEdge*>::Element *E = cluster->get_in_edges().front(); E; E = E->next()) {
		ret.push_back(Variant(E->get()));
	}

	return ret;
}

void DataGraph::get_edges_from_vertex(vid p_vid, List<DataGraphEdge*> *p_edges) {
	DataGraph::VertexCluster *cluster = get_vertex_cluster(p_vid);
	for (const List<DataGraphEdge*>::Element *E = cluster->get_out_edges().front(); E; E = E->next()) {
		p_edges->push_back(E->get());
	}
}

Array DataGraph::get_edges_from_vertex_array(vid p_vid) {
	Array ret;
	DataGraph::VertexCluster *cluster = get_vertex_cluster(p_vid);
	for (const List<DataGraphEdge*>::Element *E = cluster->get_out_edges().front(); E; E = E->next()) {
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

	//ClassDB::bind_method(D_METHOD("get_vertex", "p_vertex_id"), &DataGraph::get_vertex);
	//ClassDB::bind_method(D_METHOD("get_vertices"), &DataGraph::get_vertices);
	//ClassDB::bind_method(D_METHOD("add_vertex", "p_labels", "p_metadata"), &DataGraph::add_vertex_array);
	//ClassDB::bind_method(D_METHOD("remove_vertex", "p_vertex_id"), &DataGraph::remove_vertex);
	//ClassDB::bind_method(D_METHOD("get_num_vertices"), &DataGraph::get_num_vertices);
	//ClassDB::bind_method(D_METHOD("has_vertex", "p_vertex_id"), &DataGraph::has_vertex);

	//ClassDB::bind_method(D_METHOD("get_edge", "p_vertex_start", "p_vertex_end"), &DataGraph::get_edge);
	//ClassDB::bind_method(D_METHOD("get_edge_id", "p_edge_id"), &DataGraph::get_edge_id);
	//ClassDB::bind_method(D_METHOD("get_edges"), &DataGraph::get_edges);
	//ClassDB::bind_method(D_METHOD("add_edge", "p_vertex_start", "p_vertex_end", "p_label", "p_metadatadata"), &DataGraph::add_edge);
	//ClassDB::bind_method(D_METHOD("remove_edge", "p_edge_id"), &DataGraph::remove_edge);
	//ClassDB::bind_method(D_METHOD("get_num_edges"), &DataGraph::get_num_edges);
	//ClassDB::bind_method(D_METHOD("has_edge", "p_edge_id"), &DataGraph::has_edge);

}

DataGraph::DataGraph(const DataGraph &p_other) {
	_vertices = p_other._vertices;
	_edges = p_other._edges;
	_vertex_map = p_other._vertex_map;
	_edge_map = p_other._edge_map;
}

bool DataGraph::operator<(DataGraph &p_other) {
	bool vdiff = _vertices.size() - p_other._vertices.size();
	if (!vdiff) {

		bool ediff = _edges.size() - p_other._edges.size();

		if (ediff > 0) {
			return true;
		}

	} else if (vdiff > 0) {
		return true;
	}

	return false;
}

bool DataGraph::operator==(DataGraph &p_other) {
	return *this < p_other && p_other < *this;
}


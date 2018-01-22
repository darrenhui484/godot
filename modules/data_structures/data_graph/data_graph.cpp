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

GraphMap *DataGraphVertex::get_in_edges() {
	if (!_graph) {
		WARN_PRINT("Cannot fetch edges from vertex unaffiliated with a graph.");
		return NULL;
	}
	return _graph->get_vertex_cluster(this)->get_in_edges();
}

GraphMap *DataGraphVertex::get_out_edges() {
	if (!_graph) {
		WARN_PRINT("Cannot fetch edges from vertex unaffiliated with a graph.");
		return NULL;
	}
	return _graph->get_vertex_cluster(this)->get_out_edges();
}

Dictionary DataGraphVertex::_get_in_edges() {
	if (!_graph) {
		WARN_PRINT("Cannot fetch edges from vertex unaffiliated with a graph.");
		return Dictionary();
	}
	return DataGraph::gmap_to_dict(_graph->get_vertex_cluster(this)->get_in_edges());
}

Dictionary DataGraphVertex::_get_out_edges() {
	if (!_graph) {
		WARN_PRINT("Cannot fetch edges from vertex unaffiliated with a graph.");
		return Dictionary();
	}
	return DataGraph::gmap_to_dict(_graph->get_vertex_cluster(this)->get_out_edges());
}

bool DataGraphVertex::matches(DataGraphVertex *p_vertex) {

	for (List<StringName>::Element *E = p_vertex->_labels.front(); E; E = E->next()) {
		if (!_labels.find(E->get()))
			return false;
	}

	List<Variant> keys;
	p_vertex->_metadata.get_key_list(&keys);

	for (List<Variant>::Element *E = keys.front(); E; E = E->next()) {
		if (!_metadata.has(E->get()))
			return false;
		Variant value = p_vertex->_metadata[E->get()];
		if (value != _metadata[E->get()])
			return false;
	}

	return true;
}

void DataGraphVertex::_bind_methods() {

	ClassDB::bind_method(D_METHOD("get_labels"), &DataGraphVertex::get_labels);
	ClassDB::bind_method(D_METHOD("add_label", "p_label"), &DataGraphVertex::add_label);
	ClassDB::bind_method(D_METHOD("remove_label", "p_label"), &DataGraphVertex::remove_label);
	ClassDB::bind_method(D_METHOD("has_label", "p_label"), &DataGraphVertex::has_label);
	ClassDB::bind_method(D_METHOD("clear_labels"), &DataGraphVertex::clear_labels);

	ClassDB::bind_method(D_METHOD("set_metadata", "p_metadata_dict"), &DataGraphVertex::set_metadata);
	ClassDB::bind_method(D_METHOD("get_metadata"), &DataGraphVertex::get_metadata);

	ClassDB::bind_method(D_METHOD("get_in_edges"), &DataGraphVertex::_get_in_edges);
	ClassDB::bind_method(D_METHOD("get_out_edges"), &DataGraphVertex::_get_out_edges);

	ClassDB::bind_method(D_METHOD("matches"), &DataGraphVertex::_matches);

	ADD_PROPERTY(PropertyInfo(Variant::DICTIONARY, "metadata"), "set_metadata", "get_metadata");
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

Dictionary DataGraphEdge::get_metadata() const {
	return _metadata;
}

void DataGraphEdge::set_metadata(Dictionary p_metadata) {
	_metadata = p_metadata;
}

bool DataGraphEdge::matches(DataGraphEdge *p_edge) {

	if (p_edge->_start)
		if (p_edge->_start != _start)
			return false;
	if (p_edge->_end)
		if (p_edge->_end != _end)
			return false;
	if (p_edge->_label != StringName())
		if (p_edge->_label != _label)
			return false;

	List<Variant> keys;
	p_edge->_metadata.get_key_list(&keys);

	for (List<Variant>::Element *E = keys.front(); E; E = E->next()) {
		if (!_metadata.has(E->get()))
			return false;
		Variant value = p_edge->_metadata[E->get()];
		if (value != _metadata[E->get()])
			return false;
	}
}

void DataGraphEdge::_bind_methods() {

	ClassDB::bind_method(D_METHOD("get_start"), &DataGraphEdge::get_start);
	ClassDB::bind_method(D_METHOD("get_end"), &DataGraphEdge::get_end);
	ClassDB::bind_method(D_METHOD("get_label"), &DataGraphEdge::get_label_str);
	ClassDB::bind_method(D_METHOD("set_metadata", "p_metadata_dict"), &DataGraphEdge::set_metadata);
	ClassDB::bind_method(D_METHOD("get_metadata"), &DataGraphEdge::get_metadata);

	ClassDB::bind_method(D_METHOD("matches"), &DataGraphEdge::_matches);

	ADD_PROPERTY(PropertyInfo(Variant::NIL, "metadata"), "set_metadata", "get_metadata");
}

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

uint64_t DataGraph::id_gen = 0;

DataGraph::VertexCluster::VertexCluster(uint64_t p_id, List<StringName> *p_labels, Dictionary p_metadata)
	: _vertex(p_id) {

	if (p_labels) {
		for (List<StringName>::Element *E = p_labels->front(); E; E = E->next()) {
			_vertex.add_label(E->get());
		}
	}

	_vertex.set_metadata(p_metadata);
}

Dictionary DataGraph::VertexCluster::_get_in_edges() {
	return DataGraph::gmap_to_dict(get_in_edges());
}

Dictionary DataGraph::VertexCluster::_get_out_edges() {
	return DataGraph::gmap_to_dict(get_out_edges());
}

bool DataGraph::VertexCluster::matches(VertexCluster *p_cluster) {

	if (!_vertex.matches(&p_cluster->_vertex))
		return false;

	List<StringName> keys;
	List<uint64_t> id_keys;

	p_cluster->_in_edges.get_key_list(&keys);

	for (List<StringName>::Element *L = keys.front(); L; L = L->next()) {
		if (!_in_edges.has(L->get())) {
			return false;
		}
		GraphAssetMap *edges = &p_cluster->_in_edges[L->get()];
		edges->get_key_list(&id_keys);
		for (List<uint64_t>::Element *ID = id_keys.front(); ID; ID = ID->next()) {
			DataGraphEdge *edge = Object::cast_to<DataGraphEdge>((*edges)[ID->get()]);
			if (!_in_edges[L->get()].has(edge->_id)) {
				return false;
			}
		}
		id_keys.clear();
	}

	keys.clear();
	p_cluster->_out_edges.get_key_list(&keys);

	for (List<StringName>::Element *L = keys.front(); L; L = L->next()) {
		if (!_out_edges.has(L->get())) {
			return false;
		}
		GraphAssetMap *edges = &p_cluster->_out_edges[L->get()];
		edges->get_key_list(&id_keys);
		for (List<uint64_t>::Element *ID = id_keys.front(); ID; ID = ID->next()) {
			DataGraphEdge *edge = Object::cast_to<DataGraphEdge>((*edges)[ID->get()]);
			if (!_out_edges[L->get()].has(edge->_id)) {
				return false;
			}
		}
		id_keys.clear();
	}

	return true;
}


DataGraph::VertexCluster::VertexCluster(const DataGraph::VertexCluster &p_other) {
	_vertex = p_other._vertex;
	_in_edges = p_other._in_edges;
	_out_edges = p_other._out_edges;
}

bool DataGraph::VertexCluster::operator<(DataGraph::VertexCluster &p_other) {
	return _vertex < p_other._vertex;
}

bool DataGraph::VertexCluster::operator==(DataGraph::VertexCluster &p_other) {
	return _vertex == p_other._vertex;
}

DataGraph::VertexCluster *DataGraph::get_vertex_cluster(DataGraphVertex *p_vertex) {
	if (!p_vertex) {
		ERR_PRINT("Cannot fetch vertex with null pointer");
		return NULL;
	}
	if (p_vertex->_graph != this) {
		ERR_PRINT("Cannot fetch vertex associated with a different graph");
		return NULL;
	}
	return (DataGraph::VertexCluster*) _cluster_map[p_vertex->_labels[0]][p_vertex->_id].operator uint64_t();
}

void DataGraph::get_vertices(Set<DataGraphVertex *> *p_vertices) {
	List<StringName> keys;
	List<uint64_t> id_keys;

	_cluster_map.get_key_list(&keys);

	for (List<StringName>::Element *L = keys.front(); L; L = L->next()) {
		GraphAssetMap *clusters = &_cluster_map[L->get()];
		clusters->get_key_list(&id_keys);
		for (List<uint64_t>::Element *E = id_keys.front(); E; E = E->next()) {
			VertexCluster *cluster = (VertexCluster*) (*clusters)[E->get()].operator uint64_t();
			if (cluster && !p_vertices->has(cluster->get_vertex())) {
				p_vertices->insert(cluster->get_vertex());
			}
		}
		id_keys.clear();
	}
	keys.clear();
}

Array DataGraph::_get_vertices() {
	Array ret;

	Set<DataGraphVertex*> vertices;
	get_vertices(&vertices);

	for (Set<DataGraphVertex*>::Element *E = vertices.front(); E; E = E->next()) {
		ret.push_back(E->get());
	}

	return ret;
}

DataGraphVertex *DataGraph::add_vertex(List<StringName> *p_labels, Dictionary p_metadata) {
	VertexCluster *cluster = memnew(VertexCluster(++id_gen, p_labels, p_metadata));
	if (!p_labels) {
		_cluster_map[""][cluster->get_vertex()->_id] = cluster;
	} else {
		for (List<StringName>::Element *E = p_labels->front(); E; E = E->next()) {
			_cluster_map[E->get()][cluster->get_vertex()->_id] = cluster;
		}
	}
	return Object::cast_to<DataGraphVertex>(cluster->get_vertex());
}

DataGraphVertex *DataGraph::_add_vertex(Array p_labels, Dictionary p_metadata) {
	List<StringName> labels;
	for (int i = 0; i < p_labels.size(); ++i) {
		labels.push_back(StringName(p_labels[i]));
	}
	return add_vertex(&labels, p_metadata);
}

void DataGraph::remove_vertex(DataGraphVertex *p_vertex) {
	if (!p_vertex) {
		WARN_PRINT("Cannot remove a vertex from DataGraph with a null pointer.");
		return;
	}
	if (p_vertex->_graph != this) {
		WARN_PRINT("Cannot remove a vertex associated with another DataGraph.");
		return;
	}
	VertexCluster *cluster = get_vertex_cluster(p_vertex);
	List<StringName> keys;
	List<uint64_t> id_keys;

	//remove incoming edges
	cluster->get_in_edges()->get_key_list(&keys);

	for (List<StringName>::Element *L = keys.front(); L; L = L->next()) {
		GraphAssetMap *edges = &(*cluster->get_in_edges())[L->get()];
		edges->get_key_list(&id_keys);
		for (List<uint64_t>::Element *ID = id_keys.front(); ID; ID = ID->next()) {
			remove_edge(Object::cast_to<DataGraphEdge>((*edges)[ID->get()]));
		}
		id_keys.clear();
	}

	keys.clear();
	cluster->get_out_edges()->get_key_list(&keys);

	//remove outgoing edges
	for (List<StringName>::Element *L = keys.front(); L; L = L->next()) {
		GraphAssetMap *edges = &(*cluster->get_out_edges())[L->get()];
		edges->get_key_list(&id_keys);
		for (List<uint64_t>::Element *ID = id_keys.front(); ID; ID = ID->next()) {
			remove_edge(Object::cast_to<DataGraphEdge>((*edges)[ID->get()]));
		}
		id_keys.clear();
	}

	//remove label mappings
	for (List<StringName>::Element *E = cluster->get_vertex()->_labels.front(); E; E = E->next()) {
		_cluster_map[E->get()].erase(cluster->get_vertex()->get_id());
	}

	memdelete(cluster);
}

uint64_t DataGraph::get_num_vertices() {
	return _cache.num_vertices;
}

bool DataGraph::has_vertex(DataGraphVertex *p_vertex) {
	return p_vertex->_graph == this;
}

DataGraphEdge *DataGraph::get_edge(DataGraphVertex *p_start, DataGraphVertex *p_end) {
	DataGraph::VertexCluster *cluster = get_vertex_cluster(p_start);
	List<StringName> keys;
	List<uint64_t> id_keys;
	cluster->get_out_edges()->get_key_list(&keys);

	for (List<StringName>::Element *L = keys.front(); L; L = L->next()) {
		GraphAssetMap *edges = &(*cluster->get_out_edges())[L->get()];
		edges->get_key_list(&id_keys);
		for (List<uint64_t>::Element *ID = id_keys.front(); ID; ID = ID->next()) {
			DataGraphEdge *edge = Object::cast_to<DataGraphEdge>((*edges)[ID->get()]);
			if (edge->get_end() == p_end) {
				return edge;
			}
		}
		id_keys.clear();
	}
	return NULL;
}

void DataGraph::get_edges(List<DataGraphEdge *> *p_edges) {
	List<StringName> keys;
	List<uint64_t> id_keys;
	_edge_map.get_key_list(&keys);

	for (List<StringName>::Element *L = keys.front(); L; L = L->next()) {
		GraphAssetMap *edges = &_edge_map[L->get()];
		edges->get_key_list(&id_keys);
		for (List<uint64_t>::Element *ID = id_keys.front(); ID; ID = ID->next()) {
			DataGraphEdge *edge = Object::cast_to<DataGraphEdge>((*edges)[ID->get()]);
			p_edges->push_back(edge);
		}
		id_keys.clear();
	}
}

Array DataGraph::_get_edges() {
	Array ret;

	List<StringName> keys;
	List<uint64_t> id_keys;
	_edge_map.get_key_list(&keys);

	for (List<StringName>::Element *L = keys.front(); L; L = L->next()) {
		GraphAssetMap *edges = &_edge_map[L->get()];
		edges->get_key_list(&id_keys);
		for (List<uint64_t>::Element *ID = id_keys.front(); ID; ID = ID->next()) {
			DataGraphEdge *edge = Object::cast_to<DataGraphEdge>((*edges)[ID->get()]);
			ret.push_back(edge);
		}
		id_keys.clear();
	}

	return ret;
}

DataGraphEdge *DataGraph::add_edge(DataGraphVertex *p_start, DataGraphVertex *p_end, const StringName &p_label, Dictionary p_metadata) {
	ERR_FAIL_COND_V(!p_start, NULL);
	ERR_FAIL_COND_V(!p_end, NULL);
	ERR_FAIL_COND_V(p_start->_graph == this, NULL);
	ERR_FAIL_COND_V(p_end->_graph == this, NULL);

	DataGraphEdge *edge = memnew(DataGraphEdge(++id_gen, p_start, p_end, p_label, p_metadata));
	_edge_map[p_label][edge->_id] = edge;
	return edge;
}

Error DataGraph::remove_edge(DataGraphEdge *p_edge) {
	if (!p_edge) {
		WARN_PRINT("Cannot remove an edge from DataGraph with a null pointer.");
		return ERR_DOES_NOT_EXIST;
	}
	bool label_exists = _edge_map.has(p_edge->_label);
	Variant edge = label_exists ? _edge_map[p_edge->_label][p_edge->_id] : false;
	if (!edge) {
		WARN_PRINT(("Failed to remove non-existent edge from DataGraph: " + itos(p_edge->_id)).utf8().ptr());
		return ERR_DOES_NOT_EXIST;
	}
	_edge_map[p_edge->_label].erase(p_edge->_id);
	_cache.num_edges--;
}

size_t DataGraph::get_num_edges() {
	return _cache.num_edges;
}

bool DataGraph::has_edge(DataGraphEdge *p_edge) {
	return !p_edge || !_edge_map.has(p_edge->_label) || !_edge_map[p_edge->_label][p_edge->_id];
}

void DataGraph::get_labeled_vertices(List<StringName> *p_labels, Set<DataGraphVertex *> *p_vertices) {

	List<uint64_t> id_keys;

	for (List<StringName>::Element *L = p_labels->front(); L; L = L->next()) {
		GraphAssetMap *assets = &_cluster_map[L->get()];
		assets->get_key_list(&id_keys);
		for (List<uint64_t>::Element *ID = id_keys.front(); ID; ID = ID->next()) {
			p_vertices->insert(Object::cast_to<DataGraphVertex>((*assets)[ID->get()]));
		}
	}
}

Array DataGraph::_get_labeled_vertices(List<StringName> *p_labels) {
	Array ret;
	Set<DataGraphVertex *> vertices;

	get_labeled_vertices(p_labels, &vertices);

	for (Set<DataGraphVertex*>::Element *E = vertices.front(); E; E = E->next()) {
		ret.push_back(Variant(E->get()));
	}

	return ret;
}

void DataGraph::get_labeled_edges(const StringName &p_label, List<DataGraphEdge *> *p_edges) {

	List<uint64_t> id_keys;

	GraphAssetMap *assets = &_cluster_map[p_label];
	assets->get_key_list(&id_keys);
	for (List<uint64_t>::Element *ID = id_keys.front(); ID; ID = ID->next()) {
		p_edges->push_back(Object::cast_to<DataGraphEdge>((*assets)[ID->get()]));
	}
}

Array DataGraph::_get_labeled_edges(const StringName &p_label) {

	Array ret;

	List<uint64_t> id_keys;

	GraphAssetMap *assets = &_cluster_map[p_label];
	assets->get_key_list(&id_keys);
	for (List<uint64_t>::Element *ID = id_keys.front(); ID; ID = ID->next()) {
		ret.push_back(Object::cast_to<DataGraphEdge>((*assets)[ID->get()]));
	}

	return ret;
}

void DataGraph::clear() {
	List<StringName> keys;
	List<uint64_t> id_keys;

	_edge_map.get_key_list(&keys);

	for (List<StringName>::Element *L = keys.front(); L; L = L->next()) {
		GraphAssetMap *edges = &_edge_map[L->get()];
		edges->get_key_list(&id_keys);
		for (List<uint64_t>::Element *ID = id_keys.front(); ID; ID = ID->next()) {
			DataGraphEdge *edge = Object::cast_to<DataGraphEdge>((*edges)[ID->get()]);
			memdelete(edge);
		}
		id_keys.clear();
	}

	keys.clear();
	_cluster_map.get_key_list(&keys);

	for (List<StringName>::Element *L = keys.front(); L; L = L->next()) {
		GraphAssetMap *clusters = &_cluster_map[L->get()];
		clusters->get_key_list(&id_keys);
		for (List<uint64_t>::Element *ID = id_keys.front(); ID; ID = ID->next()) {
			VertexCluster *cluster = (VertexCluster*)(*clusters)[ID->get()].operator uint64_t();
			memdelete(cluster->get_vertex());
		}
		id_keys.clear();
	}
	keys.clear();
	_edge_map.clear();
	_cluster_map.clear();
}

bool DataGraph::matches(DataGraph *p_graph) {

	if (!p_graph)
		return false;

	List<StringName> keys;
	List<uint64_t> id_keys;

	_edge_map.get_key_list(&keys);

	for (List<StringName>::Element *L = keys.front(); L; L = L->next()) {
		if (!_edge_map.has(L->get()))
			return false;

		GraphAssetMap *edges = &_edge_map[L->get()];
		edges->get_key_list(&id_keys);
		for (List<uint64_t>::Element *ID = id_keys.front(); ID; ID = ID->next()) {
			DataGraphEdge *src = Object::cast_to<DataGraphEdge>(_edge_map[L->get()][ID->get()]);
			DataGraphEdge *target = Object::cast_to<DataGraphEdge>((*edges)[ID->get()]);
			if (!src->matches(target))
				return false;
		}
		id_keys.clear();
	}

	keys.clear();
	_cluster_map.get_key_list(&keys);

	for (List<StringName>::Element *L = keys.front(); L; L = L->next()) {
		if (!_cluster_map.has(L->get()))
			return false;

		GraphAssetMap *clusters = &_cluster_map[L->get()];
		clusters->get_key_list(&id_keys);
		for (List<uint64_t>::Element *ID = id_keys.front(); ID; ID = ID->next()) {
			DataGraphEdge *src = Object::cast_to<DataGraphEdge>(_cluster_map[L->get()][ID->get()]);
			DataGraphEdge *target = Object::cast_to<DataGraphEdge>((*clusters)[ID->get()]);
			if (!src->matches(target))
				return false;
		}
		id_keys.clear();
	}

	keys.clear();

	return true;
}

Dictionary DataGraph::gmap_to_dict(GraphMap *p_gmap) {
	Dictionary ret;
	List<StringName> keys;
	List<uint64_t> id_keys;

	p_gmap->get_key_list(&keys);

	for (List<StringName>::Element *L = keys.front(); L; L = L->next()) {
		GraphAssetMap *edges = &(*p_gmap)[L->get()];
		edges->get_key_list(&id_keys);
		ret[L->get()] = Dictionary();
		for (List<uint64_t>::Element *ID = id_keys.front(); ID; ID = ID->next()) {
			Dictionary temp = ret[L->get()];
			temp[ID->get()] = (*p_gmap)[L->get()][ID->get()];
		}
		id_keys.clear();
	}
	keys.clear();

	return ret;
}

void DataGraph::_bind_methods() {

	ClassDB::bind_method(D_METHOD("get_vertices"), &DataGraph::_get_vertices);
	ClassDB::bind_method(D_METHOD("add_vertex", "p_labels", "p_metadata"), &DataGraph::_add_vertex);
	ClassDB::bind_method(D_METHOD("remove_vertex", "p_vertex"), &DataGraph::_remove_vertex);
	ClassDB::bind_method(D_METHOD("get_num_vertices"), &DataGraph::get_num_vertices);
	ClassDB::bind_method(D_METHOD("has_vertex", "p_vertex"), &DataGraph::_has_vertex);

	ClassDB::bind_method(D_METHOD("get_edge", "p_vertex_start", "p_vertex_end"), &DataGraph::_get_edge);
	ClassDB::bind_method(D_METHOD("get_edges"), &DataGraph::_get_edges);
	ClassDB::bind_method(D_METHOD("add_edge", "p_vertex_start", "p_vertex_end", "p_label", "p_metadata"), &DataGraph::_add_edge);
	ClassDB::bind_method(D_METHOD("remove_edge", "p_edge"), &DataGraph::_remove_edge);
	ClassDB::bind_method(D_METHOD("get_num_edges"), &DataGraph::get_num_edges);
	ClassDB::bind_method(D_METHOD("has_edge", "p_edge"), &DataGraph::_has_edge);

}

DataGraph::DataGraph(const DataGraph &p_other) {
	_cluster_map = p_other._cluster_map;
	_edge_map = p_other._edge_map;
}

bool DataGraph::operator<(DataGraph &p_other) {
	bool vdiff = _cluster_map.size() - p_other._cluster_map.size();
	if (!vdiff) {

		bool ediff = _edge_map.size() - p_other._edge_map.size();

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


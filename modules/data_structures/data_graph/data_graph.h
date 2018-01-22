/*************************************************************************/
/*  data_graph.h                                                         */
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

#ifndef DATA_GRAPH_H
#define DATA_GRAPH_H

#include "reference.h"

class DataGraph;
class DataGraphEdge;

typedef HashMap<uint64_t, Variant> GraphAssetMap; // asset ID to asset pointer
typedef HashMap<StringName, GraphAssetMap, StringNameHasher> GraphMap; // label mappings

class DataGraphVertex : public Object {
	GDCLASS(DataGraphVertex, Object);

	friend class DataGraph;

private:
	uint64_t _id;
	List<StringName> _labels;
	Dictionary _metadata;
	DataGraph *_graph;

protected:
	static void _bind_methods();

	//bind helpers
	bool _matches(Object *p_vertex) {
		return matches(Object::cast_to<DataGraphVertex>(p_vertex));
	}
	Dictionary _get_in_edges();
	Dictionary _get_out_edges();

public:
	DataGraphVertex(uint64_t p_id = -1, DataGraph *p_graph = NULL) : _id(p_id), _graph(p_graph) {}
	DataGraphVertex(const DataGraphVertex &p_other);
	~DataGraphVertex() {}

	bool operator<(DataGraphVertex &p_other);
	bool operator==(DataGraphVertex &p_other);

	uint64_t get_id() const { return _id; }

	void get_label_list(List<StringName> *p_list) const;
	PoolStringArray get_labels() const;
	void add_label(const StringName &p_label);
	void remove_label(const StringName &p_label);
	bool has_label(const StringName &p_label);
	void clear_labels();

	Dictionary get_metadata() const;
	void set_metadata(Dictionary p_metadata);

	GraphMap *get_in_edges();
	GraphMap *get_out_edges();

	bool matches(DataGraphVertex *p_vertex);
};

class DataGraphEdge : public Object {
	GDCLASS(DataGraphEdge, Object);

	friend class DataGraph;

private:
	uint64_t _id;
	DataGraphVertex *_start;
	DataGraphVertex *_end;
	StringName _label;
	Dictionary _metadata;
	DataGraph *_graph;

protected:
	static void _bind_methods();

	//bind helpers
	bool _matches(Object *p_edge) {
		return matches(Object::cast_to<DataGraphEdge>(p_edge));
	}

public:
	DataGraphEdge(uint64_t p_id = -1, DataGraphVertex *p_start = NULL, DataGraphVertex *p_end = NULL, const StringName &p_label = StringName(), Dictionary p_metadata = Dictionary())
		: _id(p_id), _start(p_start), _end(p_end), _label(p_label), _metadata(p_metadata) {}
	DataGraphEdge(const DataGraphEdge &p_other);
	~DataGraphEdge() {}

	bool operator<(DataGraphEdge &p_other);
	bool operator==(DataGraphEdge &p_other);

	uint64_t get_id() const { return _id; }
	DataGraphVertex *get_start() const { return _start; }
	DataGraphVertex *get_end() const { return _end; }
	const StringName &get_label() const { return _label; }
	String get_label_str() const { return String(_label); }

	Dictionary get_metadata() const;
	void set_metadata(Dictionary p_metadata);

	bool matches(DataGraphEdge *p_edge);
};

class DataGraph : public Reference {
	GDCLASS(DataGraph, Reference);

private:

	static uint64_t id_gen;

	// a vertex and its direct inward/outward connections
	class VertexCluster {

	private:
		DataGraphVertex _vertex;
		GraphMap _in_edges; // label -> edgeId -> edge
		GraphMap _out_edges; // label -> edgeId -> edge

		Dictionary _get_in_edges();
		Dictionary _get_out_edges();

	public:
		VertexCluster(uint64_t p_id = -1, List<StringName> *p_labels = NULL, Dictionary p_metadata = Dictionary());
		VertexCluster(const VertexCluster &p_other);
		~VertexCluster() {}

		bool operator<(VertexCluster &p_other);
		bool operator==(VertexCluster &p_other);

		DataGraphVertex *get_vertex() { return &_vertex; }
		GraphMap *get_in_edges() { return &_in_edges; }
		GraphMap *get_out_edges() { return &_out_edges; }

		bool matches(VertexCluster *p_cluster);
	};

	GraphMap _cluster_map; // label -> vertex ID -> VertexCluster*
	GraphMap _edge_map; // label -> edge ID -> DataGraphEdge*

	bool _directed;

	struct {
		uint64_t num_vertices = 0;
		uint64_t num_edges = 0;
	} _cache ;

protected:
	static void _bind_methods();

	// bind helpers
	bool _has_vertex(Object *p_vertex) {
		return has_vertex(Object::cast_to<DataGraphVertex>(p_vertex));
	}
	DataGraphEdge *_get_edge(Object *p_start = NULL, Object *p_end = NULL) {
		return get_edge(Object::cast_to<DataGraphVertex>(p_start), Object::cast_to<DataGraphVertex>(p_end));
	}
	DataGraphEdge *_add_edge(Object *p_start = NULL, Object *p_end = NULL, const StringName &p_label = StringName(), Dictionary p_metadata = Dictionary()) {
		return add_edge(Object::cast_to<DataGraphVertex>(p_start), Object::cast_to<DataGraphVertex>(p_end), p_label, p_metadata);
	}
	bool _has_edge(Object *p_edge) {
		return has_edge(Object::cast_to<DataGraphEdge>(p_edge));
	}
	Array _get_edges();
	Array _get_vertices();
	Array _get_labeled_vertices(List<StringName> *p_labels);
	Array _get_labeled_edges(const StringName &p_label);
	void _remove_vertex(Object *p_vertex) {
		remove_vertex(Object::cast_to<DataGraphVertex>(p_vertex));
	}
	Error _remove_edge(Object *p_edge) {
		return remove_edge(Object::cast_to<DataGraphEdge>(p_edge));
	}

public:
	DataGraph() {}
	DataGraph(const DataGraph &p_other);
	~DataGraph() { clear(); }

	bool operator<(DataGraph &p_other);
	bool operator==(DataGraph &p_other);

	VertexCluster *get_vertex_cluster(DataGraphVertex *p_vertex);
	void get_vertices(Set<DataGraphVertex*> *p_vertices);
	DataGraphVertex *add_vertex(List<StringName> *p_labels, Dictionary p_metadata);
	DataGraphVertex *_add_vertex(Array p_labels, Dictionary p_metadata);
	void remove_vertex(DataGraphVertex *p_vertex);
	uint64_t get_num_vertices();
	bool has_vertex(DataGraphVertex *p_vertex);

	DataGraphEdge *get_edge(DataGraphVertex *p_start, DataGraphVertex *p_end);
	void get_edges(List<DataGraphEdge*> *p_edges);
	DataGraphEdge *add_edge(DataGraphVertex *p_start, DataGraphVertex *p_end, const StringName &p_label, Dictionary p_metadata);
	Error remove_edge(DataGraphEdge *p_edge);
	size_t get_num_edges();
	bool has_edge(DataGraphEdge *p_edge);

	void get_labeled_vertices(List<StringName> *p_labels, Set<DataGraphVertex*> *p_vertices);
	void get_labeled_edges(const StringName &p_label, List<DataGraphEdge*> *p_edges);

	void clear();
	bool matches(DataGraph *p_graph);

	static Dictionary gmap_to_dict(GraphMap *p_gmap);
};

#endif // DATA_GRAPH_H


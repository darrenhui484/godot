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

typedef uint32_t vid; // vertex ID
typedef uint32_t eid; // edge ID
typedef HashMap<StringName, Variant, StringNameHasher> MetaMap;

class DataGraph;
class DataGraphEdge;

class DataGraphVertex : public Object {
	GDCLASS(DataGraphVertex, Object);

	friend class DataGraph;

private:
	vid _id;
	List<StringName> _labels;
	Dictionary _metadata;
	DataGraph *_graph;

protected:
	static void _bind_methods();

	//bind helpers
	bool _matches(Object *p_vertex) {
		return matches(Object::cast_to<DataGraphVertex>(p_vertex));
	}

public:
	DataGraphVertex(vid p_vid = -1, DataGraph *p_graph = NULL) : _id(p_vid), _graph(p_graph) {}
	DataGraphVertex(const DataGraphVertex &p_other);
	~DataGraphVertex() {}

	bool operator<(DataGraphVertex &p_other);
	bool operator==(DataGraphVertex &p_other);

	vid get_id() const { return _id; }

	void get_label_list(List<StringName> *p_list) const;
	PoolStringArray get_labels() const;
	void add_label(const StringName &p_label);
	void remove_label(const StringName &p_label);
	bool has_label(const StringName &p_label);
	void clear_labels();

	Dictionary get_metadata() const;
	void set_metadata(Dictionary p_metadata);

	List<DataGraphEdge*> get_in_edges();
	List<DataGraphEdge*> get_out_edges();

	Array get_in_edges_array();
	Array get_out_edges_array();

	bool matches(DataGraphVertex *p_vertex);
};

class DataGraphEdge : public Object {
	GDCLASS(DataGraphEdge, Object);

	friend class DataGraph;

private:
	eid _id;
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
	DataGraphEdge(eid p_eid = -1, DataGraphVertex *p_start = NULL, DataGraphVertex *p_end = NULL, const StringName &p_label = StringName(), Dictionary p_metadata = Dictionary())
		: _id(p_eid), _start(p_start), _end(p_end), _label(p_label), _metadata(p_metadata) {}
	DataGraphEdge(const DataGraphEdge &p_other);
	~DataGraphEdge() {}

	bool operator<(DataGraphEdge &p_other);
	bool operator==(DataGraphEdge &p_other);

	eid get_id() const { return _id; }
	DataGraphVertex *get_start() const { return _start; }
	DataGraphVertex *get_end() const { return _end; }
	const StringName &get_label() const { return _label; }
	String get_label_str() const { return String(_label); }

	Dictionary get_metadata() const;
	void set_metadata(Dictionary p_metadata);

	bool matches(DataGraphEdge *p_edge);
};

class DataGraphPath : public Reference {
	GDCLASS(DataGraphPath, Reference);

private:

	List<DataGraphVertex*> _vertices;
	List<DataGraphEdge*> _edges;

protected:
	static void _bind_methods();

public:

	DataGraphPath();
	~DataGraphPath() {}

	bool operator<(DataGraphPath &p_other);
	bool operator==(DataGraphPath &p_other);

	void clear();
};

class DataGraph : public Reference {
	GDCLASS(DataGraph, Reference);

private:

	class VertexCluster {

		DataGraphVertex _vertex;
		List<DataGraphEdge*> _in_edges;
		List<DataGraphEdge*> _out_edges;

	public:
		VertexCluster(vid p_vid = -1, List<StringName> *p_labels = NULL, Dictionary p_metadata = Dictionary());
		VertexCluster(const VertexCluster &p_other);
		~VertexCluster() {}

		bool operator<(VertexCluster &p_other);
		bool operator==(VertexCluster &p_other);

		DataGraphVertex *get_vertex() { return &_vertex; }
		List<DataGraphEdge*> &get_in_edges() { return _in_edges; }
		List<DataGraphEdge*> &get_out_edges() { return _out_edges; }

		bool matches(VertexCluster *p_cluster);
	};

	Dictionary _vertices; //vid mapped to a VertexCluster
	Dictionary _edges; //eid mapped to a DataGraphEdge, could've been a List, but the Dictionary's hashtable would give faster access

	HashMap<StringName, List<DataGraphVertex*>, StringNameHasher> _vertex_map;
	HashMap<StringName, List<DataGraphEdge*>, StringNameHasher> _edge_map;

	bool _directed;

protected:
	static void _bind_methods();

	// bind helpers
	DataGraphEdge *_get_edge(Object *p_start = NULL, Object *p_end = NULL) {
		return get_edge(Object::cast_to<DataGraphVertex>(p_start), Object::cast_to<DataGraphVertex>(p_end));
	}
	DataGraphEdge *_add_edge(Object *p_start = NULL, Object *p_end = NULL, const StringName &p_label = StringName(), Dictionary p_metadata = Dictionary()) {
		return add_edge(Object::cast_to<DataGraphVertex>(p_start), Object::cast_to<DataGraphVertex>(p_end), p_label, p_metadata);
	}
	Array _get_vertices_with_labels(const List<StringName> &p_labels);
	Array _get_edges_with_label(const StringName &p_label);
	Array _get_labeled_vertices();
	Array _get_labeled_edges();
	void _remove_vertex(Object *p_vertex);
	Error _remove_edge(Object *p_edge);
	//Dictionary _get_matching(Object *p_graph);

public:
	DataGraph() {}
	DataGraph(const DataGraph &p_other);
	~DataGraph() {}

	bool operator<(DataGraph &p_other);
	bool operator==(DataGraph &p_other);

	DataGraphVertex *get_vertex(vid p_vid);
	VertexCluster *get_vertex_cluster(vid p_vid);
	void get_vertex_list(List<DataGraphVertex*> *p_vertices);
	Array get_vertices();
	DataGraphVertex *add_vertex(List<StringName> *p_labels, Dictionary p_metadata);
	DataGraphVertex *add_vertex_array(Array p_labels, Dictionary p_metadata);
	void remove_vertex_id(vid p_vid);
	void remove_vertex(DataGraphVertex *p_vertex);
	size_t get_num_vertices();
	bool has_vertex(vid p_vid);

	DataGraphEdge *get_edge(DataGraphVertex *p_start, DataGraphVertex *p_end);
	DataGraphEdge *get_edge_id(eid p_eid);
	void get_edge_list(List<DataGraphEdge*> *p_edges);
	Array get_edges();
	DataGraphEdge *add_edge(DataGraphVertex *p_start, DataGraphVertex *p_end, const StringName &p_label, Dictionary p_metadata);
	Error remove_edge_id(eid p_eid);
	Error remove_edge(DataGraphEdge *p_edge);
	size_t get_num_edges();
	bool has_edge(eid p_eid);
	//Dictionary get_matching(DataGraph *p_graph);

	// void

	void get_vertices_with_labels(const List<StringName> &p_labels, List<DataGraphVertex*> *p_vertices);
	void get_edges_with_label(const StringName &p_label, List<DataGraphEdge*> *p_edges);

	void get_labeled_vertices(List<StringName> *p_labels);
	void get_labeled_edges(List<StringName> *p_labels);

	void clear();
	bool matches(DataGraph *p_graph);
};

#endif // DATA_GRAPH_H


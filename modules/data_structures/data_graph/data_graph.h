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

public:
	DataGraphEdge(eid p_eid = -1, DataGraphVertex *p_start = NULL, DataGraphVertex *p_end = NULL, const StringName &p_label = "", Dictionary p_metadata = Dictionary());
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
};

class DataGraph : public Reference {
	GDCLASS(DataGraph, Reference);

private:

	class VertexCluster {

		DataGraphVertex vertex;
		List<DataGraphEdge*> in_edges;
		List<DataGraphEdge*> out_edges;

	public:
		VertexCluster(vid p_vid = -1, List<StringName> *p_labels = NULL, Dictionary p_metadata = Dictionary());
		VertexCluster(const VertexCluster &p_other);
		~VertexCluster() {}

		bool operator<(VertexCluster &p_other);
		bool operator==(VertexCluster &p_other);

		DataGraphVertex *get_vertex() { return &vertex; }
		List<DataGraphEdge*> &get_in_edges() { return in_edges; }
		List<DataGraphEdge*> &get_out_edges() { return out_edges; }
	};

	Dictionary _vertices; //vid mapped to a VertexCluster
	Dictionary _edges; //eid mapped to a DataGraphEdge, could've been a List, but the Dictionary's hashtable would give faster access

	HashMap<StringName, List<DataGraphVertex*>, StringNameHasher> _vertex_map;
	HashMap<StringName, List<DataGraphEdge*>, StringNameHasher> _edge_map;

	bool _directed;

protected:
	static void _bind_methods();

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
	void remove_vertex(vid p_vid);
	size_t get_num_vertices();
	bool has_vertex(vid p_vid);

	DataGraphEdge *get_edge(DataGraphVertex *p_start, DataGraphVertex *p_end);
	DataGraphEdge *get_edge_id(eid p_eid);
	void get_edge_list(List<DataGraphEdge*> *p_edges);
	Array get_edges();
	DataGraphEdge *add_edge(DataGraphVertex *p_start, DataGraphVertex *p_end, const StringName &p_label, Dictionary p_metadata);
	Error remove_edge(eid p_eid);
	size_t get_num_edges();
	bool has_edge(eid p_eid);

	void get_edges_to_vertex(vid p_vid, List<DataGraphEdge*> *p_edges);
	Array get_edges_to_vertex_array(vid p_vid);
	void get_edges_from_vertex(vid p_vid, List<DataGraphEdge*> *p_edges);
	Array get_edges_from_vertex_array(vid p_vid);

	// void

	void get_vertices_with_label_list(const StringName &p_label, List<DataGraphVertex*> *p_vertices);
	Array get_vertices_with_label_array(const StringName &p_label);
	void get_edges_with_label_list(const StringName &p_label, List<DataGraphEdge*> *p_edges);
	Array get_edges_with_label_array(const StringName &p_label);

	void get_vertex_label_list(List<StringName> *p_labels);
	Array get_vertex_label_array();
	void get_edge_label_list(List<StringName> *p_labels);
	Array get_edge_label_array();

	void clear();
};

#endif // DATA_GRAPH_H


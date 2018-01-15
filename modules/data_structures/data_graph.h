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

class DataGraphVertex : public Object {
	GDCLASS(DataGraphVertex, Object);

	friend class DataGraph;

private:
	vid _id;
	List<StringName> _labels;
	Dictionary _meta;

protected:
	static void _bind_methods();

public:
	DataGraphVertex(vid p_vid) : _id(p_vid) {}
	~DataGraphVertex() {}

	vid get_id() { return _id; }

	void get_label_list(List<StringName> *p_list) const;
	PoolStringArray get_labels() const;
	void add_label(const StringName &p_label);
	void remove_label(const StringName &p_label);
	bool has_label(const StringName &p_label);
	void clear_labels();

	Dictionary get_meta() const;
	void set_meta(Dictionary p_meta);
};

class DataGraphEdge : public Object {
	GDCLASS(DataGraphEdge, Object);

	friend class DataGraph;

private:
	eid _id;
	vid _start;
	vid _end;
	StringName _label;
	Dictionary _meta;
	DataGraph *_graph;

protected:
	static void _bind_methods();

public:
	DataGraphEdge(eid p_eid, vid p_start, vid p_end, const StringName &p_label, Dictionary p_meta);
	~DataGraphEdge();

	eid get_id() const { return _id; }
	vid get_start() const { return _start; }
	vid get_end() const { return _end; }
	const DataGraphVertex *get_start_vertex() const;
	const DataGraphVertex *get_end_vertex() const;
	const StringName &get_label() const { return _label; }

	Dictionary get_meta() const;
	void set_meta(Dictionary p_meta);
};

class DataGraph : public Reference {
	GDCLASS(DataGraph, Reference);

private:

	struct VertexCluster {
		DataGraphVertex vertex;
		List<DataGraphEdge*> in_edges;
		List<DataGraphEdge*> out_edges;

		VertexCluster(vid p_vid, List<StringName> *p_labels, Dictionary p_meta)
			: vertex(p_vid) {

			for (List<StringName>::Element *E = p_labels->front(); E; E = E->next()) {
				vertex.add_label(E->get());
			}

			vertex.set_meta(p_meta);
		}
	};

	Vector<VertexCluster> _vertices;
	Vector<DataGraphEdge> _edges;

	Vector<vid> _free_vids;
	Vector<eid> _free_eids;

	HashMap<StringName, List<DataGraphVertex*>, StringNameHasher> _vertex_map;
	HashMap<StringName, List<DataGraphEdge*>, StringNameHasher> _edge_map;

	bool _directed;

	VertexCluster *get_cluster(vid p_vid);

protected:
	static void _bind_methods();

public:
	DataGraph();
	~DataGraph();

	DataGraphVertex *get_vertex(vid p_vid);
	void get_vertex_list(List<DataGraphVertex*> *p_vertices);
	Array get_vertices();
	void add_vertex(List<StringName> *p_labels, Dictionary p_meta);
	void add_vertex_array(Array p_labels, Dictionary p_meta);
	void remove_vertex(vid p_vid);
	size_t get_num_vertices();
	bool has_vertex(vid p_vid);

	DataGraphEdge *get_edge(vid p_start, vid p_end);
	DataGraphEdge *get_edge_id(eid p_eid);
	void get_edge_list(List<DataGraphEdge*> *p_edges);
	Array get_edges();
	Error add_edge(vid p_start, vid p_end, const StringName &p_label, Dictionary p_meta);
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


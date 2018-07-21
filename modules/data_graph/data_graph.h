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

class DataGraphVertex : public Object {
    GDCLASS(DataGraphVertex, Object);

	friend DataGraph;

	Variant _data;
	bool _is_relationship : 1;
	DataGraph *_graph;

protected:
    static void _bind_methods();

	void _add_tags(Array p_tags);
	void _remove_tags(Array p_tags);
	bool _has_tags(Array p_tags) const;
	Array _get_tags() const;

public:

	void set_data(Variant p_metadata);
	Variant get_data() const;

	void set_graph(DataGraph *p_graph);
	DataGraph *get_graph();

	void add_tags(const List<StringName> &p_tags);
	void remove_tags(const List<StringName> &p_tags);
	bool has_tags(const List<StringName> &p_tags);
	const Set<StringName> &get_tags();
	void clear_tags();

    DataGraphVertex();
    ~DataGraphVertex();
};

class DataGraph : public Reference {
    GDCLASS(DataGraph, Reference);

	typedef Set<DataGraphVertex *> Connections;
	typedef HashMap<DataGraphVertex *, Connections, HashMapHasherDefault, HashMapComparatorDefault<DataGraphVertex> > GraphMap;

	typedef Set<DataGraphVertex *> VertexSet;
	typedef HashMap<StringName, VertexSet> TagMap;

	typedef HashMap<RefPtr, VertexSet> ScriptMap;

	GraphMap verts_in;
	GraphMap verts_out;
	TagMap tag_index;
	ScriptMap script_index;

protected:
    static void _bind_methods();

	void _add_vertex(Object *p_vertex);
	void _remove_vertex(Object *p_vertex);
public:

	void add_vertex(DataGraphVertex *p_vertex);
	void remove_vertex(DataGraphVertex *p_vertex);

	//mirrored in vertices
	void v_add_tags(DataGraphVertex *p_vertex, const List<StringName> &p_tags);
	void v_remove_tags(DataGraphVertex *p_vertex, const List<StringName> &p_tags);
	bool v_has_tags(DataGraphVertex *p_vertex, const List<StringName> &p_tags) const;
	const Set<StringName> &v_get_tags(DataGraphVertex *p_vertex) const;
	void v_clear_tags(DataGraphVertex *p_vertex);

	void clear();

    DataGraph();
    ~DataGraph();
};

#endif //DATA_GRAPH_H

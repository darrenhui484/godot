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

class DataGraphVertex : public Object {
    GDCLASS(DataGraphVertex, Object);

	Variant _metadata;

	Set<StringName> tags;

protected:
    static void _bind_methods();

	void _add_tags(Array p_tags);
	void _remove_tags(Array p_tags);
	bool _has_tags(Array p_tags) const;
	Array _get_tags() const;

public:

	void set_metadata(Variant p_metadata);
	Variant get_metadata() const;

	void add_tags(const List<StringName> &p_tags);
	void remove_tags(const List<StringName> &p_tags);
	bool has_tags(const List<StringName> &p_tags) const;
	const Set<StringName> &get_tags() const;
	void clear_tags();

    DataGraphVertex();
    ~DataGraphVertex();
};

// use obj->get_instance_id() for unique IDs
// use call() to handle the scripting side
class DataGraphLayer : public Object {
    GDCLASS(DataGraphLayer, Object);

protected:
    static void _bind_methods();

public:
	DataGraphLayer();
	~DataGraphLayer();
};

class DataGraphLayerVertexTags : public DataGraphLayer {
    GDCLASS(DataGraphLayerVertexTags, DataGraphLayer);

protected:

public:
	DataGraphLayerVertexTags();
	~DataGraphLayerVertexTags();
};


class DataGraph : public Reference {
    GDCLASS(DataGraph, Reference);

	Vector<DataGraphLayer*> layers;

	typedef Set<DataGraphVertex *> Connections;
	typedef HashMap<DataGraphVertex *, Connections, HashMapHasherDefault, HashMapComparatorDefault<DataGraphVertex> > GraphMap;

	GraphMap vertices;

protected:
    static void _bind_methods();

public:

    DataGraph();
    ~DataGraph();
};

#endif //DATA_GRAPH_H

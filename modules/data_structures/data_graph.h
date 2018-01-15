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

	friend DataGraph;

private:
	Set<String> labels;
	Variant metadata;

protected:
	static void _bind_methods();

public:
	DataGraphVertex() {}
	~DataGraphVertex() {}

	void get_label_list(List<String> *p_list) const;
	PoolStringArray get_labels() const;
	void add_label(const String &p_label) { labels.insert(p_label); }
	void remove_label(const String &p_label) { labels.erase(p_label); }
	bool has_label(const String &p_label) { return labels.has(p_label); }
	void clear_labels() { labels.clear(); }

	const Variant &get_metadata() const { return metadata; }
	void set_metadata(const Variant &p_metadata = Variant()) { metadata = p_metadata; }
};

class DataGraphEdge : public Object {
	GDCLASS(DataGraphEdge, Object);

	friend DataGraph;

private:
	uint32_t start;
	uint32_t end;
	String label;
	Variant metadata;
	DataGraph *graph;

protected:
	static void _bind_methods();

public:
	DataGraphEdge(uint32_t p_start, uint32_t p_end, const String &p_label, const Variant &p_metadata);
	~DataGraphEdge();

	uint32_t get_start() const { return start; }
	uint32_t get_end() const { return end; }
	const DataGraphVertex *get_start_vertex() const;
	const DataGraphVertex *get_end_vertex() const;
	const String &get_label() const { return label; }
	void set_metadata(const Variant &p_metadata = Variant()) { metadata = p_metadata; }
	const Variant &get_metadata() const { return metadata; }
};

struct DataGraphImplementationList;
struct DataGraphImplementationMatrix;

class DataGraph : public Reference, public DataGraphInterface {
	GDCLASS(DataGraph, Reference);

private:

	friend DataGraphEdge;

	union DataImpl {
		DataGraphImplementationList list;
		DataGraphImplementationMatrix matrix;
	} _data;

protected:
	static void _bind_methods();

public:
	DataGraph();
	~DataGraph();

	enum class Mode { GRAPH_ADJACENCY_LIST = 0, GRAPH_ADJACENCY_MATRIX = 1 };

	void set_mode(Mode p_mode);
	Mode get_mode();
};

#endif // DATA_GRAPH_H


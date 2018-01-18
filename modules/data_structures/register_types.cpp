#include "register_types.h"
#include "class_db.h"
#include "data_graph/data_graph.h"

void register_data_structures_types() {
	ClassDB::register_class<DataGraphVertex>();
	ClassDB::register_class<DataGraphEdge>();
	ClassDB::register_class<DataGraph>();
}

void unregister_data_structures_types() {

}

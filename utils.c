#include "utils.h"

//Graph duplication function
Graph* duplicate_graph(Graph *graph)
{
   Graph *graph_copy = newGraph(100000, 100000);
	 int node_mapping[graph->nodes.size];
	 //Copy nodes
	 for(int i = 0; i < graph->nodes.size; i++){
			Node *host_node = getNode(graph, i);
			if(host_node == NULL || host_node->index == -1) continue;
			node_mapping[i] = addNode(graph_copy, host_node->root, makeHostLabel(host_node->label.mark, host_node->label.length, copyHostList(host_node->label.list)));
	 }
	 //Copy edges
	 for(int i = 0; i < graph->edges.size; i++){
			Edge *host_edge = getEdge(graph, i);
			if(host_edge == NULL || host_edge->index == -1) continue;
			addEdge(graph_copy, makeHostLabel(host_edge->label.mark, host_edge->label.length, copyHostList(host_edge->label.list)), node_mapping[host_edge->source], node_mapping[host_edge->target]);
	 }
	 return graph_copy;
}

//Counts the active nodes in a GP individual.
int count_active_nodes(Graph* hostG, int inputs, int outputs){
	mark_active_blue(hostG);
	int count = 0;
	for(int host_index = 0; host_index < hostG->nodes.size; host_index++)
	{
		 Node *host_node = getNode(hostG, host_index);
		 if(host_node == NULL || host_node->index == -1) continue;
		 HostLabel label = host_node->label;
		 if(label.mark > 0){
		 	count++;
		 }
	}
	unmark_graph(hostG);
	if(count < (inputs + outputs)){
		return 0;
	}
	return count - (inputs + outputs);
}

void mark_active_blue(Graph* hostG){

	for(int host_index = 0; host_index < hostG->nodes.size; host_index++)
	{
		 Node *host_node = getNode(hostG, host_index);
		 if(host_node == NULL || host_node->index == -1) continue;

		 HostLabel label = host_node->label;
		 if(label.length != 2) break;

		 HostListItem *item = label.list->first;
		 HostListItem *item2 = item->next;
		 if(item->atom.type != 'i') break;
		 if(item2->atom.type != 's') break;
		 if(strcmp(item2->atom.str, "OUT") == 0){
	   	 changeNodeMark(hostG, host_index, 3);
			 mark_active_children_blue(hostG, host_node);
		 }
	}
}

void mark_active_children_blue(Graph* hostG, Node *node){
	int counter;
	for(counter = 0; counter < node->out_edges.size + 2; counter++)
	{
		Edge *host_edge = getNthOutEdge(hostG, node, counter);
		if(host_edge == NULL || host_edge->index == -1) continue;
		Node *target = getNode(hostG, host_edge->target);
		HostLabel label = target->label;
		if(label.mark == 0){
 	   	changeNodeMark(hostG, target->index, 3);
			mark_active_children_blue(hostG, target);
		}
	}
}

void unmark_graph(Graph* hostG){

		for(int host_index = 0; host_index < hostG->nodes.size; host_index++)
		{
			 Node *host_node = getNode(hostG, host_index);
			 if(host_node == NULL || host_node->index == -1) continue;
			 if(host_node->label.mark != 0){
		   	changeNodeMark(hostG, host_index, 0);
				if(host_node->root){
					host_node->root = false;
				}
			}
		}
}

Graph* build_empty_host_graph()
{
   Graph* new_host = newGraph(100000, 100000);
   return new_host;
}

void freeGraphArray(Graph* array, int graphs){
    for(int i = 0; i < graphs; i++){
     Graph* graph = &array[i];
     if(graph == NULL) return;
     int index;
     for(index = 0; index < graph->nodes.size; index++)
     {
        Node *node = getNode(graph, index);
        if(node == NULL) continue;
        if(node->out_edges.items != NULL) free(node->out_edges.items);
        if(node->in_edges.items != NULL) free(node->in_edges.items);
        removeHostList(node->label.list);
     }
     if(graph->nodes.holes.items) free(graph->nodes.holes.items);
     if(graph->nodes.items) free(graph->nodes.items);

     for(index = 0; index < graph->edges.size; index++)
     {
        Edge *edge = getEdge(graph, index);
        if(edge == NULL) continue;
        removeHostList(edge->label.list);
     }
     if(graph->edges.holes.items) free(graph->edges.holes.items);
     if(graph->edges.items) free(graph->edges.items);
     if(graph->root_nodes != NULL)
     {
        RootNodes *iterator = graph->root_nodes;
        while(iterator != NULL)
        {
           RootNodes *temp = iterator;
           iterator = iterator->next;
           free(temp);
        }
     }
   }
   free(array);
}

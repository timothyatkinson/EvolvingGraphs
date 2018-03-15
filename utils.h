#ifndef UTILS_H
#define UTILS_H

//C Libraries
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>

//P-GP2 Libraries
#include "common.h"
#include "debug.h"
#include "graph.h"
#include "graphStacks.h"
#include "parser.h"
#include "morphism.h"

//Util graph marking functions
void mark_active_blue(Graph* hostG);
void mark_active_children_blue(Graph* hostG, Node *node);
void unmark_graph(Graph* hostG);
//Counts the number of nodes connected to an output in a computational network
int count_active_nodes(Graph* hostG, int inputs, int outputs);
//Duplicates a graph
Graph* duplicate_graph(Graph *graph);
Graph* build_empty_host_graph();

void freeGraphArray(Graph* array, int graphs);
#endif

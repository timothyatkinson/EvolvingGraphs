#ifndef GENOP_H
#define GENOP_H

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

#include "utils.h"
#include "common_functions.h"

typedef struct GP_Dataset {
    int inputs;
    int outputs;
    int rows;
    double** data;
} GP_Dataset;

//Loads a dataset
GP_Dataset* load_data_set(char* file, int inputs, int rand_inputs, double rand_min, double rand_max, int outputs, int rows);

//Evaluates a computational network against a dataset
double gp_evaluate(Graph* individual, GP_Dataset* dataset, Function_Set* fset);

#endif

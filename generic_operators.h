#ifndef GENOP_H
#define GENOP_H

//C Libraries
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
#include <stdint.h>

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

typedef struct GP_1_plus_lambda_env{
    Graph* (*mutate)(Graph* host, Function_Set* fset, double mutation_rate);
    Function_Set* fset;
    double mutation_rate;
    int winner_index;
    int pop_size;
    double winner_score;
    bool maximise;
    bool neutral_drift;
} GP_1_plus_lambda_env;

//Loads a dataset
GP_Dataset* load_data_set(char* file, int inputs, int rand_inputs, double rand_min, double rand_max, int outputs, int rows);
void freeDataset(GP_Dataset* dataset);

//Performs a 1 plus Lambda select + select_repopulate

Graph* GP_1_plus_lambda(Graph* population, double* scores, uintptr_t GP_1_plus_lambda_env_pointer);

//Evaluates a computational network against a dataset
double gp_evaluate(Graph* individual, GP_Dataset* dataset, Function_Set* fset);

#endif

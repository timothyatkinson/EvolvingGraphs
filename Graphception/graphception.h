#ifndef GRAPHCEPTION_H
#define GRAPHCEPTION_H

#include <stdint.h>
#include "../common_functions.h"
#include "../evolutionary_algorithm.h"
#include "../generic_operators.h"
#include "../utils.h"

#include "graph.h"
#include "common.h"

typedef struct Graphception_init_env{
  Function_Set* fset;
  GP_Dataset* dataset;
  int nodes[2];
  int modules;
  int module_inputs;
  int pop_size;
} Graphception_init_env;

Graphception_init_env* default_graphception_init_env(GP_Dataset* dataset, Function_Set* fset);
GP_1_plus_lambda_env* default_graphception_select_env(Function_Set* fset);
GP_eval_env* default_graphception_eval_env(GP_Dataset* dataset, Function_Set* fset);
Target_0_env* default_graphception_termination_env();
EAArgs* default_graphception_EAArgs(GP_Dataset* dataset, Function_Set* fset);
Fixed_pop_env* default_graphception_pop_size_env();

Graph** graphception_init(uintptr_t env_pointer);
Graph* graphception_mutate(Graph* host, Function_Set* fset, double mutation_rate);

#endif

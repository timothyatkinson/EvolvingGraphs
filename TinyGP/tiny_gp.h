#ifndef TINY_GP_H
#define TINY_GP_H

#include <stdint.h>
#include "../common_functions.h"
#include "../evolutionary_algorithm.h"
#include "../generic_operators.h"
#include "../utils.h"

#include "graph.h"
#include "common.h"

typedef struct Tiny_GP_init_env{
  Function_Set* fset;
  GP_Dataset* dataset;
  int inputs;
  int outputs;
  int pop_size;
  int depth;
} Tiny_GP_init_env;

Tiny_GP_init_env* default_tiny_gp_init_env(GP_Dataset* dataset, Function_Set* fset);
GP_1_plus_lambda_env* default_tiny_gp_select_env(Function_Set* fset);
GP_eval_env* default_tiny_gp_eval_env(GP_Dataset* dataset, Function_Set* fset);
Target_x_env* default_tiny_gp_termination_env();
EAArgs* default_tiny_gp_EAArgs(GP_Dataset* dataset, Function_Set* fset);
Fixed_pop_env* default_tiny_gp_pop_size_env();

Graph** tiny_gp_init(uintptr_t env_pointer);
Graph* tiny_gp_mutate(Graph* host, Function_Set* fset, double mutation_rate);
Graph* tiny_gp_crossover(Graph* hostA, Graph* hostB, Function_Set* fset);

#endif

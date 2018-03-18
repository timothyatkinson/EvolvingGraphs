#ifndef CGP_H
#define CGP_H

#include <stdint.h>
#include "../common_functions.h"
#include "../evolutionary_algorithm.h"
#include "../generic_operators.h"
#include "../utils.h"

#include "graph.h"
#include "common.h"

typedef struct CGP_init_env{
  Function_Set* fset;
  GP_Dataset* dataset;
  int nodes;
  int max_arity;
  int pop_size;
} CGP_init_env;

CGP_init_env* default_cgp_init_env(GP_Dataset* dataset, Function_Set* fset);
GP_1_plus_lambda_env* default_cgp_select_env(Function_Set* fset);
GP_eval_env* default_cgp_eval_env(GP_Dataset* dataset, Function_Set* fset);
Target_0_env* default_cgp_termination_env();
EAArgs* default_cgp_EAArgs(GP_Dataset* dataset, Function_Set* fset);

Graph** cgp_init(uintptr_t env_pointer);
Graph* cgp_mutate(Graph* host, Function_Set* fset, double mutation_rate);

#endif

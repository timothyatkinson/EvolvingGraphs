#ifndef EGGP_DEPTH_H
#define EGGP_DEPTH_H

#include <stdint.h>
#include "../../common_functions.h"
#include "../../evolutionary_algorithm.h"
#include "../../generic_operators.h"
#include "../../utils.h"

#include "graph.h"
#include "common.h"

typedef struct EGGP_init_dc_env{
  Function_Set* fset;
  GP_Dataset* dataset;
  int nodes;
  int pop_size;
  int depth;
} EGGP_init_dc_env;



typedef struct GP_1_plus_lambda_dc_env{
    Graph* (*mutate)(Graph* host, Function_Set* fset, int depth, double mutation_rate);
    Function_Set* fset;
    double mutation_rate;
    int winner_index;
    int pop_size;
    int depth;
    double winner_score;
    bool maximise;
    bool neutral_drift;
} GP_1_plus_lambda_dc_env;

EGGP_init_dc_env* eggp_dc_init_env(GP_Dataset* dataset, Function_Set* fset, int depth);
GP_1_plus_lambda_dc_env* eggp_dc_select_env(Function_Set* fset, int depth);
GP_eval_env* eggp_dc_eval_env(GP_Dataset* dataset, Function_Set* fset);
Target_worst_x_env* eggp_dc_termination_env();
EAArgs* eggp_dc_EAArgs(GP_Dataset* dataset, Function_Set* fset, int depth);
Fixed_pop_env* eggp_dc_pop_size_env();

Graph** eggp_init_dc(uintptr_t env_pointer);
Graph* eggp_mutate_dc(Graph* host, Function_Set* fset, int depth, double mutation_rate);
Graph** GP_1_plus_lambda_dc(Graph** population, double* scores, uintptr_t GP_1_plus_lambda_dc_env_pointer);
#endif

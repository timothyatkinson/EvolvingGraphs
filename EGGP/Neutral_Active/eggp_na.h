#ifndef EGGP_NA_H
#define EGGP_NA_H

#include <stdint.h>
#include "../../common_functions.h"
#include "../../evolutionary_algorithm.h"
#include "../../generic_operators.h"
#include "../../utils.h"

#include "graph.h"
#include "common.h"

typedef struct EGGP_init_na_env{
  Function_Set* fset;
  GP_Dataset* dataset;
  int nodes;
  int pop_size;
} EGGP_init_na_env;



typedef struct GP_1_plus_lambda_na_env{
    Graph* (*mutate_a)(Graph* host, Function_Set* fset, double a_mutation_rate);
    Graph* (*mutate_n)(Graph* host, Function_Set* fset, double n_mutation_rate);
    Function_Set* fset;
    double a_mutation_rate;
    double n_mutation_rate;
    int winner_index;
    int pop_size;
    double winner_score;
    bool maximise;
    bool neutral_drift;

} GP_1_plus_lambda_na_env;

EGGP_init_na_env* eggp_na_init_env(GP_Dataset* dataset, Function_Set* fset);
GP_1_plus_lambda_na_env* eggp_na_select_env(Function_Set* fset);
GP_eval_env* eggp_na_eval_env(GP_Dataset* dataset, Function_Set* fset);
Target_x_env* eggp_na_termination_env();
EAArgs* eggp_na_EAArgs(GP_Dataset* dataset, Function_Set* fset);
Fixed_pop_env* eggp_na_pop_size_env();

Graph** eggp_init_na(uintptr_t env_pointer);
Graph* eggp_mutate_a(Graph* host, Function_Set* fset, double a_mutation_rate);
Graph* eggp_mutate_n(Graph* host, Function_Set* fset, double n_mutation_rate);
Graph** GP_1_plus_lambda_na(Graph** population, double* scores, uintptr_t GP_1_plus_lambda_na_env_pointer);
#endif

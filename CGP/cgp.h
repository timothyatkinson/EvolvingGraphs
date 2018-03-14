#ifndef CGP_H
#define CGP_H

#include <stdint.h>
#include "../common_functions.h"
#include "../evolutionary_algorithm.h"
#include "../generic_operators.h"
#include "../utils.h"

typedef struct CGP_init_env{
  Function_Set* fset;
  GP_Dataset* dataset;
  int nodes;
  int max_arity;
} CGP_init_env;

Graph* cgp_init(uintptr_t env_pointer);

#endif

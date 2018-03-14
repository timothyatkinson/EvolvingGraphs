#include "cgp.h"

Graph* cgp_init(uintptr_t env_pointer){
  CGP_init_env* env = (CGP_init_env*)env_pointer;

  Function_Set* fset = env->fset;
  GP_Dataset* dataset = env->dataset;
  int nodes = env->nodes;
  int max_arity = env->max_arity;

  
}

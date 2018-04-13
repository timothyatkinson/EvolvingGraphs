#include "graphception.h"

Graph** graphception_init(uintptr_t init_env_pointer){
  Graphception_init_env* env = (Graphception_init_env*) init_env_pointer;
  Function_Set* fset = env->fset;
  GP_Dataset* dataset = env->dataset;
  int modules = env->modules;
  int module_inputs = env->module_inputs;
  int pop_size = env->pop_size;

  Graph** population = malloc(pop_size * (modules + 1) * sizeof(Graph*));

  for(int i = 0; i < pop_size; i++){
    for(int j = 0; j < modules; j++){
      population[(i * (modules + 1)) + j] = build_empty_host_graph();
    }
    population[(i * (modules + 1)) + (modules + 1)] = build_empty_host_graph();
  }
  return population;
}

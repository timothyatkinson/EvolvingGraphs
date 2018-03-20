#include "tiny_gp.h"
#include "../evolutionary_algorithm.h"
#include "../generic_operators.h"

int main(void){
  //Reset random seed.
  srand(time(NULL));

  Tiny_GP_init_env* env = malloc(sizeof(Tiny_GP_init_env));

  Function_Set* fset = get_common_fset("add,sub,mul,div");
  GP_Dataset* dataset = load_data_set("../Datasets/SymbolicRegression/x3+x2+x1.csv", 1, 2, -1, 1, 1, 25);
  env->fset = fset;
  env->dataset = dataset;
  env->inputs = 3;
  env->outputs = 1;
  env->depth = 5;
  env->pop_size = 100;

  Graph** population = tiny_gp_init((uintptr_t)env);

  gp_print_evaluate(population[99], dataset, fset);
}

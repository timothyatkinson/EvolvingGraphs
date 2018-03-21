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
  env->depth = 3;
  env->pop_size = 100;

  Graph** population = tiny_gp_init((uintptr_t)env);

  gp_print_evaluate(population[99], dataset, fset);

  printfGraph(tiny_gp_mutate(population[99], fset, 0.33));

  Graph* dis = disjoint_union(population[98], population[99]);

  printfGraph(dis);

  printfGraph(get_red(dis));
  printfGraph(get_blue(dis));
  Graph* cros = tiny_gp_crossover(population[98], population[99]);
  printfGraph(cros);
}

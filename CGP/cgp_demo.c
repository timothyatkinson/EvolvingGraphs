#include "cgp.h"

int main(void){
  //Reset random seed.
  srand(time(NULL));
  printf("Hello world... CGP Demo here!\n");

  CGP_init_env* init_env = malloc(sizeof(CGP_init_env));
  init_env->fset = get_common_fset("and,or,nand,nor");
  init_env->dataset = load_data_set("../Datasets/SymbolicRegression/x3+x2+x1.csv", 1, 0, 0, 0, 1, 25);
  init_env->nodes = 10;
  init_env->max_arity = 2;
  init_env->pop_size = 5;
  Graph* population = cgp_init((uintptr_t)init_env);

  printf("\nOld host \n\n");

  printfGraph(&population[0]);

  Graph* new_individual = cgp_mutate(&population[0], init_env->fset, 0.2);

  printf("\nMutated Graph\n\n");

  printfGraph(new_individual);

  freeGraph(new_individual);

  double* scores = malloc(5 * sizeof(double));
  scores[0] = 0.0;
  scores[1] = 1.0;
  scores[2] = 0.0;
  scores[3] = 0.0;
  scores[4] = 0.0;

  printfGraph(&population[1]);

  GP_1_plus_lambda_env* select_env = malloc(sizeof(GP_1_plus_lambda_env));
  select_env->pop_size = 5;
  select_env->fset = init_env->fset;
  select_env->mutation_rate = 0.2;
  select_env->winner_index = -1;
  select_env->winner_score = -1.0;
  select_env->maximise = true;
  select_env->neutral_drift = true;
  select_env->mutate = cgp_mutate;

  population = GP_1_plus_lambda(population, scores, (uintptr_t)select_env);
    population = GP_1_plus_lambda(population, scores, (uintptr_t)select_env);
      population = GP_1_plus_lambda(population, scores, (uintptr_t)select_env);

  printf("\nFinal graph 2:\n\n");
  printfGraph(&population[2]);
  free_graph_array(population, 5);
  freeFset(init_env->fset);
  freeDataset(init_env->dataset);
  free(init_env);
}

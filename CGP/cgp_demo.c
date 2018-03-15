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


}

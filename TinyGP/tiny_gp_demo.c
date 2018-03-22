#include "tiny_gp.h"
#include "../evolutionary_algorithm.h"
#include "../generic_operators.h"

int main(void){
  //Reset random seed.
  //Reset random seed.
  srand(time(NULL));
  printf("Hello world... TinyGP Demo here!\n");
  Function_Set* fset = get_common_fset("add,sub,mul,div");
  GP_Dataset* dataset = load_data_set("../Datasets/SymbolicRegression/x3+x2+x1.csv", 1, 0, 0, 0, 1, 25);
  EAArgs** args = malloc(100 * sizeof(EAArgs*));
  for(int i = 0; i < 100; i++){
    args[i] = default_tiny_gp_EAArgs(dataset, fset);
  }
  run_multi(args, 100);
}

#include "eggp_dc.h"
#include "../../evolutionary_algorithm.h"

int main(void){
  //Reset random seed.
  srand(time(NULL));
  printf("Hello world... EGGP Depth Control Demo here!\n");
  Function_Set* fset = get_common_fset("add,sub,mul,div");
  GP_Dataset* dataset = load_data_set("../../Datasets/SymbolicRegression/x5-2x3+x.csv", 1, 0, 0, 0, 1, 50);
  EAArgs** args = malloc(100 * sizeof(EAArgs*));
  for(int i = 0; i < 100; i++){
    args[i] = eggp_dc_EAArgs(dataset, fset, 10);
  }
  run_multi(args, 100);
}

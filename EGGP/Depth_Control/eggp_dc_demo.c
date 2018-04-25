#include "eggp_dc.h"
#include "../../evolutionary_algorithm.h"

int main(void){
  //Reset random seed.
  srand(time(NULL));
  printf("Hello world... EGGP Depth Control Demo here!\n");
  Function_Set* fset = get_common_fset("add,sub,div,mul");
  GP_Dataset* dataset = load_data_set("../../Datasets/SymbolicRegression/x6-2x4+x2.csv", 1, 0, 0, 0, 1, 50);
  EAArgs** args = malloc(100 * sizeof(EAArgs*));
  for(int i = 0; i < 100; i++){
    args[i] = eggp_dc_EAArgs(dataset, fset, 5);
  }
  run_multi(args, 100);
}

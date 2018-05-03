#include "eggp_dc.h"
#include "../../evolutionary_algorithm.h"

int main(void){
  //Reset random seed.
  srand(time(NULL));
  printf("Hello world... EGGP Depth Control Demo here!\n");
  Function_Set* fset = get_common_fset("add,sub,mul,div");
  printf("X3+X2+X\n");
  GP_Dataset* dataset = load_data_set("../../Datasets/SymbolicRegression/x3+x2+x1.csv", 1, 1, 1, 1, 1, 25);
  EAArgs** args = malloc(100 * sizeof(EAArgs*));
   for(int i = 0; i < 100; i++){
     args[i] = eggp_dc_EAArgs(dataset, fset, 6);
   }
   run_multi(args, 100);
  // printf("X4+X3+X2+X\n");
  // dataset = load_data_set("../../Datasets/SymbolicRegression/x4+x3+x2+x1.csv", 1, 1, 1, 1, 1, 25);
  // args = malloc(100 * sizeof(EAArgs*));
  // for(int i = 0; i < 100; i++){
  //   args[i] = eggp_dc_EAArgs(dataset, fset, 6);
  // }
  // run_multi(args, 100);
  // printf("X5+X4+X3+X2+X\n");
  // dataset = load_data_set("../../Datasets/SymbolicRegression/x5+x4+x3+x2+x1.csv", 1, 1, 1, 1, 1, 25);
  // args = malloc(100 * sizeof(EAArgs*));
  // for(int i = 0; i < 100; i++){
  //   args[i] = eggp_dc_EAArgs(dataset, fset, 6);
  // }
  // run_multi(args, 100);
  // printf("X6+X5+X4+X3+X2+X\n");
  // dataset = load_data_set("../../Datasets/SymbolicRegression/x6+x5+x4+x3+x2+x1.csv", 1, 1, 1, 1, 1, 25);
  // args = malloc(100 * sizeof(EAArgs*));
  // for(int i = 0; i < 100; i++){
  //   args[i] = eggp_dc_EAArgs(dataset, fset, 6);
  // }
  // run_multi(args, 100);
  printf("X5-2X3+X\n");
  dataset = load_data_set("../../Datasets/SymbolicRegression/x5-2x3+x.csv", 1, 0,0,0, 1, 50);
args = malloc(100 * sizeof(EAArgs*));
  for(int i = 0; i < 100; i++){
    args[i] = eggp_dc_EAArgs(dataset, fset, 10);
  }
  run_multi(args, 100);
  printf("X6-2X4+2X\n");
  dataset = load_data_set("../../Datasets/SymbolicRegression/x6-2x4+x2.csv", 1, 0,0,0, 1, 50);
  args = malloc(100 * sizeof(EAArgs*));
  for(int i = 0; i < 100; i++){
    args[i] = eggp_dc_EAArgs(dataset, fset, 10);
  }
  run_multi(args, 100);
}

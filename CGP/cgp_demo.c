#include "cgp.h"
#include "../evolutionary_algorithm.h"

int main(void){
  //Reset random seed.
  srand(time(NULL));
  printf("Hello world... CGP Demo here!\n");
  Function_Set* fset = get_common_fset("and,or,nand,nor");
  GP_Dataset* dataset = load_data_set("../Datasets/Circuits/1BitAdder.csv", 3, 0, 0, 0, 2, 8);
  EAArgs** args = malloc(100 * sizeof(EAArgs*));
  for(int i = 0; i < 100; i++){
    args[i] = default_cgp_EAArgs(dataset, fset);
  }
  run_multi(args, 100);
}

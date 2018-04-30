#include "eggp.h"
#include "../evolutionary_algorithm.h"

int main(void){
  //Reset random seed.
  srand(time(NULL));
  printf("Hello world... EGGP Demo here!\n");
  Function_Set* fset = get_common_fset("and,or,nand,nor");
  GP_Dataset* dataset = load_data_set("../Datasets/Circuits/3BitAdder.csv", 7, 0, 0, 0, 4, 128);
  EAArgs** args = malloc(100 * sizeof(EAArgs*));
  for(int i = 0; i < 100; i++){
    args[i] = default_eggp_EAArgs(dataset, fset);
  }
  run_multi(args, 100);
}

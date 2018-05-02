#include "eggp_na.h"
#include "../../evolutionary_algorithm.h"

int main(void){
  //Reset random seed.
  srand(time(NULL));
  printf("Hello world... EGGP Neutral Active Demo here!\n");
  Function_Set* fset = get_common_fset("and,or,nand,nor");
  GP_Dataset* dataset = load_data_set("../../Datasets/Circuits/2BitAdder.csv", 5, 0, 0, 0, 3, 32);
  EAArgs** args = malloc(100 * sizeof(EAArgs*));
  for(int i = 0; i < 100; i++){
    args[i] = eggp_na_EAArgs(dataset, fset);
  }
  run_multi(args, 100);
}

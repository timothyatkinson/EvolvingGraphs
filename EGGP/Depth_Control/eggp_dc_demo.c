#include "eggp_dc.h"
#include "../../evolutionary_algorithm.h"

int main(void){
  //Reset random seed.
  srand(time(NULL));
  printf("Hello world... EGGP Depth Control Demo here!\n");
  Function_Set* fset = get_common_fset("and,or,nand,nor");
  GP_Dataset* dataset = load_data_set("../../Datasets/Circuits/1BitAdder.csv", 3, 0, 0, 0, 2, 8);
  EAArgs** args = malloc(100 * sizeof(EAArgs*));
  for(int i = 0; i < 100; i++){
    //args[i] = default_eggp_EAArgs(dataset, fset);
  }
  EGGP_init_dc_env* init_env = eggp_dc_init_env(dataset, fset, 5);
  Graph** pop = eggp_init_dc((uintptr_t)init_env);
  printfGraph(pop[0]);
  //run_multi(args, 100);
}

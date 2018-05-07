#include "eggp.h"
#include "../evolutionary_algorithm.h"

int main(void){
  //Reset random seed.
  srand(time(NULL));
  printf("Hello world... EGGP Demo here!\n");
  printf("AND OR NOT SHUFFLE 1BA\n");
  Function_Set* fset = get_common_fset("and,or,not");
  GP_Dataset* dataset = load_data_set("../Datasets/Circuits/1BitAdder.csv", 3, 0, 0, 0, 2, 8);
  EAArgs** args = malloc(100 * sizeof(EAArgs*));
  for(int i = 0; i < 100; i++){
    args[i] = default_eggp_EAArgs(dataset, fset);
  }
  run_multi(args, 100);
  printf("AND OR NOT2 SHUFFLE 1BA\n");
  fset = get_common_fset("and,or,not2");
  dataset = load_data_set("../Datasets/Circuits/1BitAdder.csv", 3, 0, 0, 0, 2, 8);
  args = malloc(100 * sizeof(EAArgs*));
  for(int i = 0; i < 100; i++){
    args[i] = default_eggp_EAArgs(dataset, fset);
  }
  run_multi(args, 100);
  printf("AND OR NOT2 NO SHUFFLE 1BA\n");
  fset = get_common_fset("and,or,not2");
  dataset = load_data_set("../Datasets/Circuits/1BitAdder.csv", 3, 0, 0, 0, 2, 8);
  args = malloc(100 * sizeof(EAArgs*));
  for(int i = 0; i < 100; i++){
    args[i] = default_eggp_EAArgs(dataset, fset);
    ((GP_1_plus_lambda_env*)args[i]->select_repopulate_env_pointer)->mutate = eggp_mutate_nosf;
  }
  run_multi(args, 100);
  printf("AND OR NOT SHUFFLE 2BA\n");
  fset = get_common_fset("and,or,not");
  dataset = load_data_set("../Datasets/Circuits/2BitAdder.csv", 5, 0, 0, 0, 3, 32);
  args = malloc(100 * sizeof(EAArgs*));
  for(int i = 0; i < 100; i++){
    args[i] = default_eggp_EAArgs(dataset, fset);
  }
  run_multi(args, 100);
  printf("AND OR NOT2 SHUFFLE 2BA\n");
  fset = get_common_fset("and,or,not2");
  dataset = load_data_set("../Datasets/Circuits/2BitAdder.csv", 5, 0, 0, 0, 3, 32);
  args = malloc(100 * sizeof(EAArgs*));
  for(int i = 0; i < 100; i++){
    args[i] = default_eggp_EAArgs(dataset, fset);
  }
  run_multi(args, 100);
  printf("AND OR NOT2 NO SHUFFLE 2BA\n");
  fset = get_common_fset("and,or,not2");
  dataset = load_data_set("../Datasets/Circuits/2BitAdder.csv", 5, 0, 0, 0, 3, 32);
  args = malloc(100 * sizeof(EAArgs*));
  for(int i = 0; i < 100; i++){
    args[i] = default_eggp_EAArgs(dataset, fset);
    ((GP_1_plus_lambda_env*)args[i]->select_repopulate_env_pointer)->mutate = eggp_mutate_nosf;
  }
  run_multi(args, 100);
}

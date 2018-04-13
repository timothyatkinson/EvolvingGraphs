#include "graphception.h"
#include "../evolutionary_algorithm.h"

int main(void){
  //Reset random seed.
  srand(time(NULL));
  printf("Hello world... GraphCeption Demo here!\n");
  Function_Set* fset = get_common_fset("and,or,nand,nor");
  GP_Dataset* dataset = load_data_set("../Datasets/Circuits/1BitAdder.csv", 3, 0, 0, 0, 2, 8);
}

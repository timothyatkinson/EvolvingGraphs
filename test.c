#include "generic_operators.h"
#include "common_functions.h"
#include "evolutionary_algorithm.h"
#include "utils.h"
/* A file for testing various aspects of the Evolving Graphs library */

int main(void){

  //Reset random seed.
  srand(time(NULL));

  //Libraries compile.
  printf("\nHello world! You have successfully compiled Evolving Graphs.\n\n");

  //Load a local dataset.
  GP_Dataset* dataset = load_data_set("Datasets/SymbolicRegression/x3+x2+x1.csv", 1, 5, -5, 5, 1, 25);
  free(dataset);

  printf("\nIf you can see a 7 x 25 table above, you have successfully loaded a GP dataset.\n");
  printf("The first 5 columns are randomly generated variables in [-5,5], the 6th is x and the 7th is the function to learn y = x^3 + x^2 + x.\n\n");

  //Create a function set {+,-,*,/}

  Function_Set* fset = get_common_fset("add,sub,div,mul");
  print_fset(fset);
  free(fset);

  printf("\nIf you can see a function set above containing {+,-,*,/} you have successfully loaded a function set.\n");
  printf("The value in brackets after each function is that function's arity.\n\n");

}

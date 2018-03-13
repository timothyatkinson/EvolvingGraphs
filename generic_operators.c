#include "generic_operators.h"

GP_Dataset* loadDataSet(char* file, int inputs, int rand_inputs, double rand_min, double rand_max, int outputs, int rows){
  Dataset* dataset = malloc(sizeof(Dataset));
  dataset->inputs = inputs + rand_inputs;
  dataset->outputs = outputs;
  dataset->rows = rows;
  dataset->data = malloc((rows * (inputs + rand_inputs + outputs)) * sizeof(double));
  double * raw[rows];
  for(int i = 0; i < rows; i++){
    dataset->data[i] = malloc((inputs + rand_inputs + outputs) * sizeof(double));
    for(int j = 0; j < inputs + outputs; j++){
      dataset->data[i][j] = -1.0;
    }
  }
  FILE* fp = fopen(file, "r");
  if(fp == NULL){
      printf("Error: file %s cannot be found.\n", file);
      exit(0);
  }
  for (int i = 0; i < rows; i++){
    for(int j = 0; j < (inputs + outputs); j++){
      int r = fscanf(fp," %lf %*c",&dataset->data[i][j]);
      if(r != 1){
        printf("Error: file %s does not match the given row and columns dimensions.\n", file);
        exit(0);
      }
    }
  }
	printf("Rows: %d\n", rows);
  for(int i = 0; i < rows; i++){
    for(int j = 0; j < inputs + outputs; j++){
      printf("%lf, ", dataset->data[i][j]);
    }
    printf("\n");
  }
  return dataset;
}

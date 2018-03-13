
#include "common_functions.h"

typedef struct GP_Dataset {
    int inputs;
    int outputs;
    int rows;
    double** data;
} GP_Dataset;
GP_Dataset* loadDataSet(char* file, int inputs, int rand_inputs, double rand_min, double rand_max, int outputs, int rows);

double gp_evaluate(Graph* individual, GP_Dataset* dataset);

//C Libraries
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>

//P-GP2 Libraries
#include "common.h"
#include "debug.h"
#include "graph.h"
#include "graphStacks.h"
#include "parser.h"
#include "morphism.h"

typedef struct EAArgs {
  Graph* initialisation(int init_env_pointer);
  int init_env_pointer;
  double* evaluate(Graph* population, int evaluation_env_pointer);
  int evaluation_env_pointer;
  Graph* select_repopulate(Graph* population, double* scores, int select_repopulate_env_pointer);
  int select_repopulate_env_pointer;
  bool termination(Graph* population, double* scores, int termination_env_pointer);
  int termination_env_pointer;
  bool maximise;
  int update;
  int generations;
} EAArgs;

typedef struct Result {
  double winning_score;
  Graph* winning_graph;
  int generation;
  bool terminated;
} Result;

Result* runEA(EAArgs* args);

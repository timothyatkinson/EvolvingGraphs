#include "eggp_na.h"
#include "pgp2/eggp_na_init/eggp_na_init.h"
#include "pgp2/a_node/a_node.h"
#include "pgp2/n_node/n_node.h"
#include "pgp2/a_edge/a_edge.h"
#include "pgp2/n_edge/n_edge.h"

//Util functions to prepare and clean a graph in the mutation procedure eggp_mutate
static void prepare_graph_mutate(Graph* host, Function_Set* fset);
static void clean_graph_mutate(Graph* host);

//Util functions to prepare and clean a graph in the intialisation procedure eggp_init
static void prepare_graph_init(Graph* host, Function_Set* fset, int inputs, int outputs, int nodes);
static void clean_graph_init(Graph* host);


//Function for comparing two scores
static bool compare(double candidate, double champion, bool maximise, bool neutral_drift);

//A default environment for initialisation of a EGGP individual
EGGP_init_na_env* eggp_na_init_env(GP_Dataset* dataset, Function_Set* fset){
  EGGP_init_na_env* env = malloc(sizeof(EGGP_init_na_env));
  env->fset = fset;
  env->dataset = dataset;
  env->nodes = 100;
  env->pop_size = 5;
  return env;
}


//Generates a population of EGGP individuals.
Graph** eggp_init_na(uintptr_t env_pointer){
  //Access initialisation environment using pointer
  EGGP_init_na_env* env = (EGGP_init_na_env*)env_pointer;

  //Pull variables from environment structure
  Function_Set* fset = env->fset;
  GP_Dataset* dataset = env->dataset;
  int inputs = dataset->inputs;
  int outputs = dataset->outputs;
  int nodes = env->nodes;
  int pop_size = env->pop_size;

  Graph** population = malloc(pop_size * sizeof(Graph*));

  for(int i = 0; i < pop_size; i++){
    //Prepare empty graph
    population[i] = build_empty_host_graph();

    //Load graph with variables
    prepare_graph_init(population[i], fset, inputs, outputs, nodes);

    //Generate EGGP individuals
    eggp_na_init_execute(population[i]);

    //Cleanup graph (removing meta data from prepare_graph_init)
    clean_graph_init(population[i]);
  }
  //Return
  return population;
}

//A default environment for running 1 plus lambda for EGGP
GP_1_plus_lambda_na_env* eggp_na_select_env(Function_Set* fset){
  GP_1_plus_lambda_na_env* env = malloc(sizeof(GP_1_plus_lambda_na_env));
  env->mutate_a = eggp_mutate_a;
  env->mutate_n = eggp_mutate_n;
  env->pop_size = 5;
  env->a_mutation_rate = 0.01;
  env->n_mutation_rate = 0.01;
  env->winner_index = -1;
  env->winner_score = 99999999.9;
  env->fset = fset;
  env->neutral_drift = true;
  env->maximise = false;
  return env;
}


//Mutates a EGGP individual (copies the individual, rather than overwriting).
Graph* eggp_mutate_a(Graph* host, Function_Set* fset, double a_mutation_rate){
  //Copy the individual to mutate
  Graph* new_graph = duplicate_graph(host);

  //Prepare the graph by loading in function set
  prepare_graph_mutate(new_graph, fset);
  //int nodes = count_active_nodes(host, 0, 0);
  //int edges = count_active_edges(host);
  int nodes = new_graph->nodes.size;
  int edges = new_graph->edges.size;
  int mutations = 0;
  int num = nodes + edges;
  for(int i = 0; i < num; i++){
    double r = ((double)rand() / (double)RAND_MAX);
    if(r <= a_mutation_rate){
      double r2 = ((double)rand() / (double)RAND_MAX);
      if(r2 <= ((double)edges / (double)(num))){
        a_edge_execute(new_graph);
        mutations++;
      }
      else{
        a_node_execute(new_graph);
        mutations++;
      }
    }
  }

  if(mutations == 0){
    double r = ((double)rand() / (double)RAND_MAX);
    if(r <= ((double)edges / (double)(num))){
      a_edge_execute(new_graph);
    }
    else{
      a_node_execute(new_graph);
    }
  }

  //Clean graph (removing meta data from prepare_graph_mutate)
  clean_graph_mutate(new_graph);

  return new_graph;
}


//Mutates a EGGP individual (copies the individual, rather than overwriting).
Graph* eggp_mutate_n(Graph* host, Function_Set* fset, double n_mutation_rate){
  //Copy the individual to mutate
  Graph* new_graph = duplicate_graph(host);

  //Prepare the graph by loading in function set
  prepare_graph_mutate(new_graph, fset);
  int nodes = new_graph->nodes.size - count_active_nodes(host, 0, 0);
  int edges = new_graph->edges.size - count_active_edges(host);
  int mutations = 0;
  int num = nodes + edges;
  for(int i = 0; i < num; i++){
    double r = ((double)rand() / (double)RAND_MAX);
    if(r <= n_mutation_rate){
      double r2 = ((double)rand() / (double)RAND_MAX);
      if(r2 <= ((double)edges / (double)(num))){
        n_edge_execute(new_graph);
        mutations++;
      }
      else{
        n_node_execute(new_graph);
        mutations++;
      }
    }
  }

  if(mutations == 0){
    double r = ((double)rand() / (double)RAND_MAX);
    if(r <= ((double)edges / (double)(num))){
      n_edge_execute(new_graph);
    }
    else{
      n_node_execute(new_graph);
    }
  }

  //Clean graph (removing meta data from prepare_graph_mutate)
  clean_graph_mutate(new_graph);

  return new_graph;
}

//A default environment for evaluating GP individuals using gp_evaluate_population
GP_eval_env* eggp_na_eval_env(GP_Dataset* dataset, Function_Set* fset){
  GP_eval_env* env = malloc(sizeof(GP_eval_env));
  env->dataset = dataset;
  env->fset = fset;
  env->pop_size = 5;
  return env;
}


Target_x_env* eggp_na_termination_env(){
  Target_x_env* env = malloc(sizeof(Target_x_env));
  env->pop_size = 5;
  env->x = 0.01;
  return env;
}

Fixed_pop_env* eggp_na_pop_size_env(){
  Fixed_pop_env* env = malloc(sizeof(Fixed_pop_env));
  env->pop_size = 5;
  return env;
}

EAArgs* eggp_na_EAArgs(GP_Dataset* dataset, Function_Set* fset){
  uintptr_t init_pointer = (uintptr_t)eggp_na_init_env(dataset, fset);
  uintptr_t select_pointer = (uintptr_t)eggp_na_select_env(fset);
  uintptr_t eval_pointer = (uintptr_t)eggp_na_eval_env(dataset, fset);
  uintptr_t term_pointer = (uintptr_t)eggp_na_termination_env();
  uintptr_t pop_pointer = (uintptr_t)eggp_na_pop_size_env();
  EAArgs* args = malloc(sizeof(EAArgs));
  args->initialisation = eggp_init_na;
  args->init_env_pointer = init_pointer;
  args->evaluate = gp_evaluate_population;
  args->evaluation_env_pointer = eval_pointer;
  args->select_repopulate = GP_1_plus_lambda_na;
  args->select_repopulate_env_pointer = select_pointer;
  args->termination = target_x;
  args->termination_env_pointer = term_pointer;
  args->pop_size = fixed_pop_size;
  args->pop_size_env_pointer = pop_pointer;
  args->maximise = false;
  args->generations = 20000000;
  args->update = 1;
  return args;
}

//A procedure for performing 1 + lambda selection and reproduction
Graph** GP_1_plus_lambda_na(Graph** population, double* scores, uintptr_t GP_1_plus_lambda_na_env_pointer){
  //Access 1 + lambda environment using pointer
  GP_1_plus_lambda_na_env* env = (GP_1_plus_lambda_na_env*)GP_1_plus_lambda_na_env_pointer;
  Function_Set* fset = env->fset;
  double a_mutation_rate = env->a_mutation_rate;
  double n_mutation_rate = env->n_mutation_rate;
  int winner_index = env->winner_index;
  double winner_score = env->winner_score;
  int pop_size = env->pop_size;
  bool maximise = env->maximise;
  bool neutral_drift = env->neutral_drift;

  //Find generation's "winning" parent
  int parent = winner_index;
  double best_score = winner_score;
  for(int i = 0; i < pop_size; i++){
    if(i != winner_index && compare(scores[i], best_score, maximise, neutral_drift)){
      parent = i;
      best_score = scores[i];
    }
  }

  Graph* p = population[parent];
  population[parent] = env->mutate_n(p, fset, n_mutation_rate);
  freeGraph(p);
  //We now know the next generation's parent
  env->winner_index = parent;
  env->winner_score = best_score;
  Graph** new_pop = malloc(pop_size * sizeof(Graph*));
  for(int i = 0; i < pop_size; i++){
    if(i != parent){
      new_pop[i] = env->mutate_a(population[parent], fset, a_mutation_rate);
    }
    else{
      new_pop[i] = duplicate_graph(population[parent]);
    }
  }
  free_graph_array(population, pop_size);
  return new_pop;
}


//Util function for preparing a graph for generating a EGGP individual
static void prepare_graph_init(Graph* host, Function_Set* fset, int inputs, int outputs, int nodes){
  /* Initialise host graph */
  /* INPUTS */
  for(int i = 0; i < inputs; i++){
    //Add a node for each input labelled i:"IN" where i is the number of the input and "IN" indicates that it is indeed an input
    HostAtom array[3];
    HostLabel label;
    array[0].type = 'i';
    array[0].num = i;
    array[1].type = 'i';
    array[1].num = 0;
    array[2].type = 's';
    array[2].str = "IN";
    HostList *list = makeHostList(array, 3, false);
    label = makeHostLabel(0, 3, list);
    addNode(host, 0, label);
  }

  /* OUTPUTS */
  for(int i = 0; i < outputs; i++){
    //Add a node for each output labelled i:"OUT" where i is the number of the output and "OUT" indicates that it is indeed an output
    HostAtom array[2];
    HostLabel label;
    array[0].type = 'i';
    array[0].num = i;
    array[1].type = 's';
    array[1].str = "OUT";
    HostList *list = makeHostList(array, 2, false);
    label = makeHostLabel(0, 2, list);
    addNode(host, 0, label);
  }

  /* FUNCTIONSET */
  Function* f = fset->first;
  for(int i = 0; i < fset->functionCount; i++){
    //Add a rooted node for each function labelled "FunctionSet":f:a where f is the string representation of the function and a is the arity.
     HostAtom array[3];
     HostLabel label;
     array[0].type = 's';
     array[0].str = "FunctionSet";
     array[1].type = 's';
     array[1].str = f->name;
     array[2].type = 'i';
     array[2].num = f->arity;
     HostList *list = makeHostList(array, 3, false);
     label = makeHostLabel(0, 3, list);
     addNode(host, 1, label);
     f = f->next;
  }

  /* NODES */
  //Add a rooted node labelled "Nodes":n where n is the number of nodes to add.
   HostAtom array[2];
   HostLabel label;
   array[0].type = 's';
   array[0].str = "Nodes";
   array[1].type = 'i';
   array[1].num = nodes;
   HostList *list = makeHostList(array, 2, false);
   label = makeHostLabel(0, 2, list);
   addNode(host, 1, label);
}

static void clean_graph_init(Graph* host){
  /* REMOVE FUNCTION SET AND NODES COUNTER. These are the only rooted nodes. */
  for(int i = 0; i < host->nodes.size; i++){
     Node *host_node = getNode(host, i);
   if(host_node == NULL) continue;
   if(!host_node->root) continue;
   removeNode(host, i);
  }
}

//Util function for preparing a graph for mutating a EGGP_na individual
static void prepare_graph_mutate(Graph* host, Function_Set* fset){
  /* Initialise host graph */
  /* FUNCTIONSET */
  Function* f = fset->first;
  for(int i = 0; i < fset->functionCount; i++){
    //Add a rooted node for each function labelled "FunctionSet":f:a where f is the string representation of the function and a is the function's arity.
     HostAtom array[3];
     HostLabel label;
     array[0].type = 's';
     array[0].str = "FunctionSet";
     array[1].type = 's';
     array[1].str = f->name;
     array[2].type = 'i';
     array[2].num = f->arity;
     HostList *list = makeHostList(array, 3, false);
     label = makeHostLabel(0, 3, list);
     addNode(host, 1, label);
     f = f->next;
  }
}

static void clean_graph_mutate(Graph* host){
  /* REMOVE FUNCTION SET AND NODES COUNTER. These are the only rooted nodes. */
  for(int i = 0; i < host->nodes.size; i++){
   Node *host_node = getNode(host, i);
   if(host_node == NULL) continue;
   if(!host_node->root) continue;
   removeNode(host, i);
  }
}

static bool compare(double candidate, double champion, bool maximise, bool neutral_drift){
  if(maximise){
    if(candidate > champion || (candidate >= champion - 0.00000001 && neutral_drift)){
      return true;
    }
    return false;
  }
  else{
    if(candidate < champion || (candidate <= champion + 0.00000001 && neutral_drift)){
      return true;
    }
    return false;
  }
}

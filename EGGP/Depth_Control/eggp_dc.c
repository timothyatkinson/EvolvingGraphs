#include "eggp_dc.h"
#include "pgp2/eggp_dc_init/eggp_dc_init.h"

//Util functions to prepare and clean a graph in the mutation procedure eggp_mutate
static void prepare_graph_mutate(Graph* host, Function_Set* fset, int depth);
static void clean_graph_mutate(Graph* host);

//Util functions to prepare and clean a graph in the intialisation procedure eggp_init
static void prepare_graph_init(Graph* host, Function_Set* fset, int inputs, int outputs, int nodes, int depth);
static void clean_graph_init(Graph* host);


//Function for comparing two scores
static bool compare(double candidate, double champion, bool maximise, bool neutral_drift);

//A default environment for initialisation of a EGGP individual
EGGP_init_dc_env* eggp_dc_init_env(GP_Dataset* dataset, Function_Set* fset, int depth){
  EGGP_init_dc_env* env = malloc(sizeof(EGGP_init_dc_env));
  env->fset = fset;
  env->dataset = dataset;
  env->nodes = 100;
  env->pop_size = 5;
  env->depth = depth;
  return env;
}


//Generates a population of EGGP individuals.
Graph** eggp_init_dc(uintptr_t env_pointer){
  //Access initialisation environment using pointer
  EGGP_init_dc_env* env = (EGGP_init_dc_env*)env_pointer;

  //Pull variables from environment structure
  Function_Set* fset = env->fset;
  GP_Dataset* dataset = env->dataset;
  int inputs = dataset->inputs;
  int outputs = dataset->outputs;
  int nodes = env->nodes;
  int pop_size = env->pop_size;
  int depth = env->depth;

  Graph** population = malloc(pop_size * sizeof(Graph*));

  for(int i = 0; i < pop_size; i++){
    //Prepare empty graph
    population[i] = build_empty_host_graph();

    //Load graph with variables
    prepare_graph_init(population[i], fset, inputs, outputs, nodes, depth);

    //Generate EGGP individuals
    eggp_dc_init_execute(population[i]);

    //Cleanup graph (removing meta data from prepare_graph_init)
    clean_graph_init(population[i]);
  }
  //Return
  return population;
}

//A default environment for running 1 plus lambda for EGGP
GP_1_plus_lambda_dc_env* eggp_dc_select_env(Function_Set* fset, int depth){
  GP_1_plus_lambda_dc_env* env = malloc(sizeof(GP_1_plus_lambda_dc_env));
  //env->mutate = eggp_mutate_dc;
  env->pop_size = 5;
  env->mutation_rate = 0.01;
  env->winner_index = -1;
  env->winner_score = 99999999.9;
  env->fset = fset;
  env->neutral_drift = true;
  env->maximise = false;
  env->depth = depth;
  return env;
}

//A default environment for evaluating GP individuals using gp_evaluate_population
GP_eval_env* eggp_dc_eval_env(GP_Dataset* dataset, Function_Set* fset){
  GP_eval_env* env = malloc(sizeof(GP_eval_env));
  env->dataset = dataset;
  env->fset = fset;
  env->pop_size = 5;
  return env;
}

Target_0_env* eggp_dc_termination_env(){
  Target_0_env* env = malloc(sizeof(Target_0_env));
  env->pop_size = 5;
  return env;
}

Fixed_pop_env* eggp_dc_pop_size_env(){
  Fixed_pop_env* env = malloc(sizeof(Fixed_pop_env));
  env->pop_size = 5;
  return env;
}

EAArgs* eggp_dc_EAArgs(GP_Dataset* dataset, Function_Set* fset, int depth){
  uintptr_t init_pointer = (uintptr_t)eggp_dc_init_env(dataset, fset, depth);
  uintptr_t select_pointer = (uintptr_t)eggp_dc_select_env(fset, depth);
  uintptr_t eval_pointer = (uintptr_t)eggp_dc_eval_env(dataset, fset);
  uintptr_t term_pointer = (uintptr_t)eggp_dc_termination_env();
  uintptr_t pop_pointer = (uintptr_t)eggp_dc_pop_size_env();
  EAArgs* args = malloc(sizeof(EAArgs));
  args->initialisation = eggp_init_dc;
  args->init_env_pointer = init_pointer;
  args->evaluate = gp_evaluate_population;
  args->evaluation_env_pointer = eval_pointer;
  args->select_repopulate = GP_1_plus_lambda_dc;
  args->select_repopulate_env_pointer = select_pointer;
  args->termination = target_0;
  args->termination_env_pointer = term_pointer;
  args->pop_size = fixed_pop_size;
  args->pop_size_env_pointer = pop_pointer;
  args->maximise = false;
  args->generations = 20000000;
  args->update = 1;
  return args;
}

//A procedure for performing 1 + lambda selection and reproduction
Graph** GP_1_plus_lambda_dc(Graph** population, double* scores, uintptr_t GP_1_plus_lambda_dc_env_pointer){
  //Access 1 + lambda environment using pointer
  GP_1_plus_lambda_dc_env* env = (GP_1_plus_lambda_dc_env*)GP_1_plus_lambda_dc_env_pointer;
  Function_Set* fset = env->fset;
  double mutation_rate = env->mutation_rate;
  int winner_index = env->winner_index;
  int winner_score = env->winner_score;
  int pop_size = env->pop_size;
  int depth = env->depth;
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

  //We now know the next generation's parent
  env->winner_index = parent;
  env->winner_score = best_score;
  Graph** new_pop = malloc(pop_size * sizeof(Graph*));
  for(int i = 0; i < pop_size; i++){
    if(i != parent){
      new_pop[i] = env->mutate(population[parent], fset, depth, mutation_rate);
    }
    else{
      new_pop[i] = duplicate_graph(population[parent]);
    }
  }
  free_graph_array(population, pop_size);
  return new_pop;
}


//Util function for preparing a graph for generating a EGGP individual
static void prepare_graph_init(Graph* host, Function_Set* fset, int inputs, int outputs, int nodes, int depth){
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

   /* NODES */
   //Add a rooted node labelled "Depth":n where n is the max depth of nodes to add.
    HostAtom array2[2];
    HostLabel label2;
    array2[0].type = 's';
    array2[0].str = "Depth";
    array2[1].type = 'i';
    array2[1].num = depth;
    HostList *list2 = makeHostList(array2, 2, false);
    label2 = makeHostLabel(0, 2, list2);
    addNode(host, 1, label2);
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

//Util function for preparing a graph for mutating a EGGP_DC individual
static void prepare_graph_mutate(Graph* host, Function_Set* fset, int depth){
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
  /* NODES */
  //Add a rooted node labelled "Depth":n where n is the max depth of nodes to add.
  HostAtom array2[2];
  HostLabel label2;
  array2[0].type = 's';
  array2[0].str = "Depth";
  array2[1].type = 'i';
  array2[1].num = depth;
  HostList *list2 = makeHostList(array2, 2, false);
  label2 = makeHostLabel(0, 2, list2);
  addNode(host, 1, label2);
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
    if(candidate > champion || (candidate >= champion && neutral_drift)){
      return true;
    }
    return false;
  }
  else{
    if(candidate < champion || (candidate <= champion && neutral_drift)){
      return true;
    }
    return false;
  }
}

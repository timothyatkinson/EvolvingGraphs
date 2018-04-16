#include "eggp.h"
#include "pgp2/eggp_mutate_node_shuffle/eggp_mutate_node_shuffle.h"
#include "pgp2/eggp_mutate_edge/eggp_mutate_edge.h"
#include "pgp2/eggp_mutate_node/eggp_mutate_node.h"
#include "pgp2/eggp_init/eggp_init.h"

//Util functions to prepare and clean a graph in the mutation procedure eggp_mutate
static void prepare_graph_mutate(Graph* host, Function_Set* fset);
static void clean_graph_mutate(Graph* host);

//Util functions to prepare and clean a graph in the intialisation procedure eggp_init
static void prepare_graph_init(Graph* host, Function_Set* fset, int inputs, int outputs, int nodes);
static void clean_graph_init(Graph* host);


//A default environment for initialisation of a EGGP individual
EGGP_init_env* default_eggp_init_env(GP_Dataset* dataset, Function_Set* fset){
  EGGP_init_env* env = malloc(sizeof(EGGP_init_env));
  env->fset = fset;
  env->dataset = dataset;
  env->nodes = 100;
  env->pop_size = 5;
  return env;
}

//A default environment for running 1 plus lambda for EGGP
GP_1_plus_lambda_env* default_eggp_select_env(Function_Set* fset){
  GP_1_plus_lambda_env* env = malloc(sizeof(GP_1_plus_lambda_env));
  env->mutate = eggp_mutate;
  env->pop_size = 5;
  env->mutation_rate = 0.01;
  env->winner_index = -1;
  env->winner_score = 99999999.9;
  env->fset = fset;
  env->neutral_drift = true;
  env->maximise = false;
  return env;
}

//A default environment for evaluating GP individuals using gp_evaluate_population
GP_eval_env* default_eggp_eval_env(GP_Dataset* dataset, Function_Set* fset){
  GP_eval_env* env = malloc(sizeof(GP_eval_env));
  env->dataset = dataset;
  env->fset = fset;
  env->pop_size = 5;
  return env;
}

Target_0_env* default_eggp_termination_env(){
  Target_0_env* env = malloc(sizeof(Target_0_env));
  env->pop_size = 5;
  return env;
}

Fixed_pop_env* default_eggp_pop_size_env(){
  Fixed_pop_env* env = malloc(sizeof(Fixed_pop_env));
  env->pop_size = 5;
  return env;
}

EAArgs* default_eggp_EAArgs(GP_Dataset* dataset, Function_Set* fset){
  uintptr_t init_pointer = (uintptr_t)default_eggp_init_env(dataset, fset);
  uintptr_t select_pointer = (uintptr_t)default_eggp_select_env(fset);
  uintptr_t eval_pointer = (uintptr_t)default_eggp_eval_env(dataset, fset);
  uintptr_t term_pointer = (uintptr_t)default_eggp_termination_env();
  uintptr_t pop_pointer = (uintptr_t)default_eggp_pop_size_env();
  EAArgs* args = malloc(sizeof(EAArgs));
  args->initialisation = eggp_init;
  args->init_env_pointer = init_pointer;
  args->evaluate = gp_evaluate_population;
  args->evaluation_env_pointer = eval_pointer;
  args->select_repopulate = GP_1_plus_lambda;
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

EAArgs* generate_eggp_EAArgs(GP_Dataset* dataset, Function_Set* fset, int nodes, int pop_size, double mutation_rate){
  return NULL;
}


//Generates a population of EGGP individuals.
Graph** eggp_init(uintptr_t env_pointer){
  //Access initialisation environment using pointer
  EGGP_init_env* env = (EGGP_init_env*)env_pointer;

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
    eggp_init_execute(population[i]);

    //Cleanup graph (removing meta data from prepare_graph_init)
    clean_graph_init(population[i]);
  }

  //Return
  return population;
}

//Mutates a EGGP individual (copies the individual, rather than overwriting).
Graph* eggp_mutate(Graph* host, Function_Set* fset, double mutation_rate){

  int max_arity = get_max_arity(fset);
  //Copy the individual to mutate
  Graph* new_graph = duplicate_graph(host);

  //Prepare the graph by loading in function set
  prepare_graph_mutate(new_graph, fset);
  //Go through nodes in ordering, mutating functions and edges
  for(int i = 0; i < new_graph->nodes.size; i++){
     Node *host_node = getNode(new_graph, i);

    //Checks if the node exists, is not rooted (e.g. not a function set node), has the correct format and is not an input node (which cannot be mutated)
    if(host_node == NULL || host_node->index == -1) continue;
    if(host_node->root) continue;
    HostLabel label = host_node->label;
    HostListItem *item = label.list->last;
    if(item->atom.type != 's') break;

    if(strcmp(item->atom.str, "IN") == 0) continue;

    if (strcmp(item->atom.str, "OUT") != 0){
        //Function mutation is possible
        double r = ((double)rand() / (double)RAND_MAX);
        if(r <= mutation_rate){
          eggp_mutate_node_shuffle_execute(new_graph);
        }

    }

    //Edge mutations. Can be done for output and function nodes.
    int counter;
    for(counter = 0; counter < host_node->out_edges.size + 2; counter++)
    {
       Edge *host_edge = getNthOutEdge(new_graph, host_node, counter);

       //Check edge exists and is not a loop
       if(host_edge == NULL || host_edge->index == -1) continue;
       if(host_edge->source == host_edge->target) continue;

       //Edge mutation is possible
       double r = ((double)rand() / (double)RAND_MAX);
       if(r <= mutation_rate){
         eggp_mutate_edge_execute(new_graph);
       }

     }
  }

  //Clean graph (removing meta data from prepare_graph_mutate)
  clean_graph_mutate(new_graph);

  return new_graph;
}

//Util function for preparing a graph for generating a EGGP individual
static void prepare_graph_init(Graph* host, Function_Set* fset, int inputs, int outputs, int nodes){
  /* Initialise host graph */
  /* INPUTS */
  for(int i = 0; i < inputs; i++){
    //Add a node for each input labelled i:"IN" where i is the number of the input and "IN" indicates that it is indeed an input
    HostAtom array[2];
    HostLabel label;
    array[0].type = 'i';
    array[0].num = i;
    array[1].type = 's';
    array[1].str = "IN";
    HostList *list = makeHostList(array, 2, false);
    label = makeHostLabel(0, 2, list);
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

//Util function for preparing a graph for mutating a CGP individual
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

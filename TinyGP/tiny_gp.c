#include "tiny_gp.h"
#include "tiny_gp_init/tiny_gp_init.h"
#include "tiny_gp_node_mutate/tiny_gp_node_mutate.h"
#include "tiny_gp_const_mutate/tiny_gp_const_mutate.h"
#include "tiny_gp_crossover/tiny_gp_crossover.h"

//Util functions to prepare and clean a graph in the intialisation procedure tiny_gp_init
static void prepare_graph_init(Graph* host, Function_Set* fset, int inputs, int outputs, int depth);
static void clean_graph_init(Graph* host);

//Util functions to prepare and clean a graph in the mutation procedure cgp_mutate
static void prepare_graph_mutate(Graph* host, Function_Set* fset);
static void clean_graph_mutate(Graph* host);

Tiny_GP_init_env* default_tiny_gp_init_env(GP_Dataset* dataset, Function_Set* fset){
  Tiny_GP_init_env* env = malloc(sizeof(Tiny_GP_init_env));
  env->fset =fset;
  env->dataset = dataset;
  env->depth = 5;
  env->pop_size = 100;
  env->inputs = dataset->inputs;
  env->outputs = dataset->outputs;
  return env;
}

GP_tournament_env* default_tiny_gp_select_env(Function_Set* fset){
  GP_tournament_env* env = malloc(sizeof(GP_tournament_env));
  env->fset = fset;
  env->mutation_rate = 0.05;
  env->mutate = tiny_gp_mutate;
  env->crossover = tiny_gp_crossover;
  env->crossover_p = 0.9;
  env->tournament_size = 3;
  env->pop_size = 100;
  env->maximise = false;
  return env;
}

//A default environment for evaluating GP individuals using gp_evaluate_population
GP_eval_env* default_tiny_gp_eval_env(GP_Dataset* dataset, Function_Set* fset){
  GP_eval_env* env = malloc(sizeof(GP_eval_env));
  env->dataset = dataset;
  env->fset = fset;
  env->pop_size = 100;
  return env;
}

Target_x_env* default_tiny_gp_termination_env(){
  Target_x_env* env = malloc(sizeof(Target_x_env));
  env->pop_size = 100;
  env->x = 0.01;
  return env;
}

Fixed_pop_env* default_tiny_gp_pop_size_env(){
  Fixed_pop_env* env = malloc(sizeof(Fixed_pop_env));
  env->pop_size = 100;
  return env;
}

EAArgs* default_tiny_gp_EAArgs(GP_Dataset* dataset, Function_Set* fset){
  uintptr_t init_pointer = (uintptr_t)default_tiny_gp_init_env(dataset, fset);
  uintptr_t select_pointer = (uintptr_t)default_tiny_gp_select_env(fset);
  uintptr_t eval_pointer = (uintptr_t)default_tiny_gp_eval_env(dataset, fset);
  uintptr_t term_pointer = (uintptr_t)default_tiny_gp_termination_env();
  uintptr_t pop_pointer = (uintptr_t)default_tiny_gp_pop_size_env();
  EAArgs* args = malloc(sizeof(EAArgs));
  args->initialisation = tiny_gp_init;
  args->init_env_pointer = init_pointer;
  args->evaluate = gp_evaluate_population;
  args->evaluation_env_pointer = eval_pointer;
  args->select_repopulate = GP_tournament_selection;
  args->select_repopulate_env_pointer = select_pointer;
  args->termination = target_x;
  args->termination_env_pointer = term_pointer;
  args->pop_size = fixed_pop_size;
  args->pop_size_env_pointer = pop_pointer;
  args->maximise = false;
  args->generations = 100;
  args->update = 1;
  return args;
}

//Generates a population of CGP individuals.
Graph** tiny_gp_init(uintptr_t env_pointer){
  //Access initialisation environment using pointer
  Tiny_GP_init_env* env = (Tiny_GP_init_env*)env_pointer;

  //Pull variables from environment structure
  Function_Set* fset = env->fset;
  GP_Dataset* dataset = env->dataset;
  int inputs = dataset->inputs;
  int outputs = dataset->outputs;
  int depth = env->depth;
  int pop_size = env->pop_size;

  Graph** population = malloc(pop_size * sizeof(Graph*));

  for(int i = 0; i < pop_size; i++){
    //Prepare empty graph
    population[i] = build_empty_host_graph();

    //Load graph with variables
    prepare_graph_init(population[i], fset, inputs, outputs, depth);

    //Generate CGP individuals
    tiny_gp_init_execute(population[i]);

    //Cleanup graph (removing meta data from prepare_graph_init)
    clean_graph_init(population[i]);
  }

  //Return
  return population;
}

//Mutates a TinyGP individual.
Graph* tiny_gp_mutate(Graph* host, Function_Set* fset, double mutation_rate){
    //Loop through all nodes. If they are a function node, we can mutate it to another function.
    //Copy the individual to mutate
    Graph* new_graph = duplicate_graph(host);

    //Prepare the graph by loading in function set
    prepare_graph_mutate(new_graph, fset);

    //Go through nodes in ordering, mutating functions and edges
    for(int i = 0; i < new_graph->nodes.size; i++){
       Node *host_node = getNode(new_graph, i);


      //Checks if the node exists, is not rooted (e.g. not a function set node), has the correct format and is not an input node (which cannot be mutated)
      if(host_node == NULL) continue;
      if(host_node->root) continue;
      HostLabel label = host_node->label;
      HostListItem *item = label.list->last;
      if(item->atom.type != 's') break;

      if(strcmp(item->atom.str, "IN") == 0) continue;

      if (strcmp(item->atom.str, "OUT") != 0){
          //Function mutation is possible
          double r = ((double)rand() / (double)RAND_MAX);
          if(r <= mutation_rate){
            changeNodeMark(new_graph, i, 3);
            tiny_gp_node_mutate_execute(new_graph);
          }

      }

      //Loop through constants - these are outgoing edges to the "IN" nodes. If we find one we can mutate it to another constant.
      int counter;
      for(counter = 0; counter < host_node->out_edges.size + 2; counter++)
      {
         Edge *host_edge = getNthOutEdge(new_graph, host_node, counter);

         //Check edge exists and is not a loop
         if(host_edge == NULL) continue;
         if(host_edge->source == host_edge->target) continue;

         Node* target = getTarget(new_graph, host_edge);
         if(strcmp(target->label.list->last->atom.str, "IN") == 0){
           double r = ((double)rand() / (double)RAND_MAX);
           if(r <= mutation_rate){
             changeEdgeMark(new_graph, host_edge->index, 3);
             tiny_gp_const_mutate_execute(new_graph);
             if(host_edge->label.mark == 3){
                 changeEdgeMark(new_graph, host_edge->index, 0);
             }
           }
         }
      }

    }

    //Clean graph (removing meta data from prepare_graph_mutate)
    clean_graph_mutate(new_graph);

    return new_graph;
}

//Swaps two random sub-trees. Returns a graph with one child red and one child blue... these can be extracted with util.c's get_red and get_blue functions.
Graph* tiny_gp_crossover(Graph* hostA, Graph* hostB){
  Graph* together = disjoint_union(hostA, hostB);

  tiny_gp_crossover_execute(together);

  return together;
}

//Util function for preparing a graph for generating a TinyGP individual
static void prepare_graph_init(Graph* host, Function_Set* fset, int inputs, int outputs, int depth){
  /* Initialise host graph */
  /* INPUTS */
  for(int i = 0; i < inputs; i++){
    //Add a node for each input labelled i:x:"IN" where i is the number of the input, x is the ordering of the input node and "IN" indicates that it is indeed an input
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
    //Add a node for each output labelled i:x:"OUT" where i is the number of the output, x is the ordering of the output node and "OUT" indicates that it is indeed an output
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
    //Add a rooted node for each function labelled "FunctionSet":f:a where f is the string representation of the function and a function's arity.
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

  /* Depth */
  //Add a rooted node labelled "Depth":d where d is the depth to generate to.
   HostAtom array[2];
   HostLabel label;
   array[0].type = 's';
   array[0].str = "Depth";
   array[1].type = 'i';
   array[1].num = depth;
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

//Util function for preparing a graph for mutating a Tiny_GP individual
static void prepare_graph_mutate(Graph* host, Function_Set* fset){
  /* Initialise host graph */
  /* FUNCTIONSET */
  Function* f = fset->first;
  for(int i = 0; i < fset->functionCount; i++){
    //Add a rooted node for each function labelled "FunctionSet":f:a where f is the string representation of the function and a is the maximum arity.
     HostAtom array[3];
     HostLabel label;
     array[0].type = 's';
     array[0].str = "FunctionSet";
     array[1].type = 's';
     array[1].str = f->name;
     array[2].type = 'i';
     //Assume all functions have max arity.
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

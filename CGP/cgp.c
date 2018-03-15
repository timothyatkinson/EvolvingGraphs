#include "cgp.h"
#include "cgp_init/cgp_init.h"
#include "cgp_mutate_node/cgp_mutate_node.h"

//Util functions to prepare and clean a graph in the mutation procedure cgp_mutate
static void prepare_graph_mutate(Graph* host, Function_Set* fset, int max_arity);
static void clean_graph_mutate(Graph* host);

//Util functions to prepare and clean a graph in the intialisation procedure cgp_init
static void prepare_graph_init(Graph* host, Function_Set* fset, int inputs, int outputs, int nodes, int max_arity);
static void clean_graph_init(Graph* host);

//Generates a population of CGP individuals.
Graph* cgp_init(uintptr_t env_pointer){
  //Access initialisation environment using pointer
  CGP_init_env* env = (CGP_init_env*)env_pointer;

  //Pull variables from environment structure
  Function_Set* fset = env->fset;
  GP_Dataset* dataset = env->dataset;
  int inputs = dataset->inputs;
  int outputs = dataset->outputs;
  int nodes = env->nodes;
  int max_arity = env->max_arity;
  int pop_size = env->pop_size;

  Graph* population = malloc(pop_size * sizeof(Graph));

  for(int i = 0; i < pop_size; i++){
    //Prepare empty graph
    population[i] = *build_empty_host_graph();

    //Load graph with variables
    prepare_graph_init(&population[i], fset, inputs, outputs, nodes, max_arity);

    //Generate CGP individuals
    cgp_init_execute(&population[i]);

    //Cleanup graph (removing meta data from prepare_graph_init)
    clean_graph_init(&population[i]);
  }

  //Return
  return population;
}

//Mutates a CGP individual (copies the individual, rather than overwriting).
Graph* cgp_mutate(Graph* host, Function_Set* fset, int max_arity, double mutation_rate){

  //Copy the individual to mutate
  Graph* new_graph = duplicate_graph(host);

  //Prepare the graph by loading in function set
  prepare_graph_mutate(new_graph, fset, max_arity);

  //Go through nodes in ordering, mutating functions and edges
  for(int i = 0; i < host->nodes.size; i++){
     Node *host_node = getNode(host, i);


    //Checks if the node exists, is not rooted (e.g. not a function node), has the correct format and is not an input node (which cannot be mutated)
    if(host_node == NULL) continue;
    if(host_node->root) continue;

    HostListItem *item = label.list->last;
    if(item->atom.type != 's') break;

    if(strcmp(item, "IN") == 0) continue;

    if (strcmp(item, "OUT") != 0){
        //Function mutation is possible

    }

    //Edge mutations. Can be done for output and function nodes.
    int counter;
    for(counter = 0; counter < host_node->out_edges.size + 2; counter++)
    {
       Edge *host_edge = getNthOutEdge(MutateFeedForwardEdge_host, host_node, counter);

       //Check edge exists and is not a loop
       if(host_edge == NULL) continue;
       if(host_edge->source == host_edge->target) continue;

       
     }
  }

  //Clean graph (removing meta data from prepare_graph_mutate)
  clean_graph_mutate(new_graph);

  return new_graph;
}

//Util function for preparing a graph for generating a CGP individual
static void prepare_graph_init(Graph* host, Function_Set* fset, int inputs, int outputs, int nodes, int max_arity){
  /* Initialise host graph */
  /* INPUTS */
  for(int i = 0; i < inputs; i++){
    //Add a node for each input labelled i:x:"IN" where i is the number of the input, x is the ordering of the input node and "IN" indicates that it is indeed an input
    HostAtom array[3];
    HostLabel label;
    array[0].type = 'i';
    array[0].num = i;
    array[1].type = 'i';
    array[1].num = i;
    array[2].type = 's';
    array[2].str = "IN";
    HostList *list = makeHostList(array, 3, false);
    label = makeHostLabel(0, 2, list);
    addNode(host, 0, label);
  }

  /* OUTPUTS */
  for(int i = 0; i < outputs; i++){
    //Add a node for each output labelled i:x:"OUT" where i is the number of the output, x is the ordering of the output node and "OUT" indicates that it is indeed an output
    HostAtom array[3];
    HostLabel label;
    array[0].type = 'i';
    array[0].num = i;
    array[1].type = 'i';
    array[1].num = i + nodes + inputs - 1;
    array[2].type = 's';
    array[2].str = "OUT";
    HostList *list = makeHostList(array, 3, false);
    label = makeHostLabel(0, 2, list);
    addNode(host, 0, label);
  }

  /* FUNCTIONSET */
  Function* f = fset->first;
  for(int i = 0; i < fset->functionCount; i++){
    //Add a rooted node for each function labelled "FunctionSet":f:a where f is the string representation of the function and a is the maximum arity.
     HostAtom array[3];
     HostLabel label;
     array[0].type = 's';
     array[0].str = "FunctionSet";
     array[1].type = 's';
     array[1].str = strdup(f->name);
     array[2].type = 'i';
     //Assume all functions have max arity.
     array[2].num = max_arity;
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

   /* INPUTS */
   //Add a rooted node labelled "Inputs":i where i is the number of inputs.
    HostAtom array2[2];
    HostLabel label2;
    array2[0].type = 's';
    array2[0].str = "Inputs";
    array2[1].type = 'i';
    array2[1].num = inputs;
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

//Util function for preparing a graph for mutating a CGP individual
static void prepare_graph_mutate(Graph* host, Function_Set* fset, int max_arity){
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
     array[1].str = strdup(f->name);
     array[2].type = 'i';
     //Assume all functions have max arity.
     array[2].num = max_arity;
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

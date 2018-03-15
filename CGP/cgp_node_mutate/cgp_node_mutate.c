#include <time.h>
#include "common.h"
#include "debug.h"
#include "graph.h"
#include "graphStacks.h"
#include "parser.h"
#include "morphism.h"

#include "cgp_node_mutate_mutate_node.h"
Morphism *M_cgp_node_mutate_mutate_node = NULL;

static void cgp_node_mutate_freeMorphisms(void)
{
   freeMorphism(M_cgp_node_mutate_mutate_node);
}

Graph* cgp_node_mutate_host = NULL;
int* cgp_node_mutate_node_map = NULL;
MorphismPot* cgp_node_mutate_pot = NULL;

static void cgp_node_mutate_garbageCollect(void)
{
   cgp_node_mutate_freeMorphisms();
   freePot(cgp_node_mutate_pot);
}

bool cgp_node_mutate_success = true;

int cgp_node_mutate_execute(Graph* host_graph)
{
   cgp_node_mutate_host = host_graph;
   cgp_node_mutate_success = true;
   cgp_node_mutate_pot = makeMorphismPot();
   emptyPot(cgp_node_mutate_pot);
   M_cgp_node_mutate_mutate_node = makeMorphism(2, 0, 4);

   /* Rule Call */
   emptyPot(cgp_node_mutate_pot);
   fillpotcgp_node_mutate_mutate_node(cgp_node_mutate_pot, M_cgp_node_mutate_mutate_node);
   if(potSize(cgp_node_mutate_pot) > 0){
      MorphismHolder *holder = drawFromPot(cgp_node_mutate_pot);
      duplicateMorphism(holder->morphism, M_cgp_node_mutate_mutate_node, cgp_node_mutate_host);
      freeMorphism(holder->morphism);
      free(holder);
      applycgp_node_mutate_mutate_node(M_cgp_node_mutate_mutate_node, false);
      cgp_node_mutate_success = true;
   }
   else
   {
      printf("No output graph: rule cgp_node_mutate_mutate_node not applicable.\n");
      cgp_node_mutate_garbageCollect();
      return 0;
   }
   emptyPot(cgp_node_mutate_pot);
   cgp_node_mutate_garbageCollect();
   return 0;
}


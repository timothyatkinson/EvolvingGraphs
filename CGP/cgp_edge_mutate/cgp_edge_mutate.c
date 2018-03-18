#include <time.h>
#include "common.h"
#include "debug.h"
#include "graph.h"
#include "graphStacks.h"
#include "parser.h"
#include "morphism.h"

#include "cgp_edge_mutate_mutate_edge.h"
Morphism *M_cgp_edge_mutate_mutate_edge = NULL;

static void cgp_edge_mutate_freeMorphisms(void)
{
   freeMorphism(M_cgp_edge_mutate_mutate_edge);
}

Graph* cgp_edge_mutate_host = NULL;
int* cgp_edge_mutate_node_map = NULL;
MorphismPot* cgp_edge_mutate_pot = NULL;

static void cgp_edge_mutate_garbageCollect(void)
{
   cgp_edge_mutate_freeMorphisms();
   freePot(cgp_edge_mutate_pot);
}

bool cgp_edge_mutate_success = true;

int cgp_edge_mutate_execute(Graph* host_graph)
{
   cgp_edge_mutate_host = host_graph;
   cgp_edge_mutate_success = true;
   cgp_edge_mutate_pot = makeMorphismPot();
   emptyPot(cgp_edge_mutate_pot);
   M_cgp_edge_mutate_mutate_edge = makeMorphism(3, 1, 8);

   /* Rule Call */
   emptyPot(cgp_edge_mutate_pot);
   fillpotcgp_edge_mutate_mutate_edge(cgp_edge_mutate_pot, M_cgp_edge_mutate_mutate_edge);
   if(potSize(cgp_edge_mutate_pot) > 0){
      MorphismHolder *holder = drawFromPot(cgp_edge_mutate_pot);
      duplicateMorphism(holder->morphism, M_cgp_edge_mutate_mutate_edge, cgp_edge_mutate_host);
      freeMorphism(holder->morphism);
      free(holder);
      applycgp_edge_mutate_mutate_edge(M_cgp_edge_mutate_mutate_edge, false);
      cgp_edge_mutate_success = true;
   }
   else
   {
      printf("No output graph: rule cgp_edge_mutate_mutate_edge not applicable.\n");
      cgp_edge_mutate_garbageCollect();
      return 0;
   }
   emptyPot(cgp_edge_mutate_pot);
   cgp_edge_mutate_garbageCollect();
   return 0;
}


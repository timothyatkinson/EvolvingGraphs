#include <time.h>
#include "common.h"
#include "debug.h"
#include "graph.h"
#include "graphStacks.h"
#include "parser.h"
#include "morphism.h"

#include "cgp_init_add_node.h"
Morphism *M_cgp_init_add_node = NULL;

static void cgp_init_freeMorphisms(void)
{
   freeMorphism(M_cgp_init_add_node);
}

Graph* cgp_init_host = NULL;
int* cgp_init_node_map = NULL;
MorphismPot* cgp_init_pot = NULL;

static void cgp_init_garbageCollect(void)
{
   cgp_init_freeMorphisms();
   freePot(cgp_init_pot);
}

bool cgp_init_success = true;

int cgp_init_execute(Graph* host_graph)
{
   cgp_init_host = host_graph;
   cgp_init_success = true;
   cgp_init_pot = makeMorphismPot();
   emptyPot(cgp_init_pot);
   M_cgp_init_add_node = makeMorphism(1, 0, 0);

   /* Rule Call */
   if(matchcgp_init_add_node(M_cgp_init_add_node))
   {
      applycgp_init_add_node(M_cgp_init_add_node, false);
      cgp_init_success = true;
   }
   else
   {
      printf("No output graph: rule cgp_init_add_node not applicable.\n");
      cgp_init_garbageCollect();
      return 0;
   }
   cgp_init_garbageCollect();
   return 0;
}


#include <time.h>
#include "common.h"
#include "debug.h"
#include "graph.h"
#include "graphStacks.h"
#include "parser.h"
#include "morphism.h"

#include "tiny_gp_crossover_crossover_point.h"
Morphism *M_tiny_gp_crossover_crossover_point = NULL;

static void tiny_gp_crossover_freeMorphisms(void)
{
   freeMorphism(M_tiny_gp_crossover_crossover_point);
}

Graph* tiny_gp_crossover_host = NULL;
int* tiny_gp_crossover_node_map = NULL;
MorphismPot* tiny_gp_crossover_pot = NULL;

static void tiny_gp_crossover_garbageCollect(void)
{
   tiny_gp_crossover_freeMorphisms();
   freePot(tiny_gp_crossover_pot);
}

bool tiny_gp_crossover_success = true;

int tiny_gp_crossover_execute(Graph* host_graph)
{
   tiny_gp_crossover_host = host_graph;
   tiny_gp_crossover_success = true;
   tiny_gp_crossover_pot = makeMorphismPot();
   emptyPot(tiny_gp_crossover_pot);
   M_tiny_gp_crossover_crossover_point = makeMorphism(4, 2, 6);

   /* Rule Call */
   emptyPot(tiny_gp_crossover_pot);
   fillpottiny_gp_crossover_crossover_point(tiny_gp_crossover_pot, M_tiny_gp_crossover_crossover_point);
   if(potSize(tiny_gp_crossover_pot) > 0){
      MorphismHolder *holder = drawFromPot(tiny_gp_crossover_pot);
      duplicateMorphism(holder->morphism, M_tiny_gp_crossover_crossover_point, tiny_gp_crossover_host);
      freeMorphism(holder->morphism);
      free(holder);
      applytiny_gp_crossover_crossover_point(M_tiny_gp_crossover_crossover_point, false);
      tiny_gp_crossover_success = true;
   }
   else
   {
      printf("No output graph: rule tiny_gp_crossover_crossover_point not applicable.\n");
      tiny_gp_crossover_garbageCollect();
      return 0;
   }
   emptyPot(tiny_gp_crossover_pot);
   tiny_gp_crossover_garbageCollect();
   return 0;
}


#include <time.h>
#include "common.h"
#include "debug.h"
#include "graph.h"
#include "graphStacks.h"
#include "parser.h"
#include "morphism.h"

#include "tiny_gp_const_mutate_mutate_input.h"
Morphism *M_tiny_gp_const_mutate_mutate_input = NULL;

static void tiny_gp_const_mutate_freeMorphisms(void)
{
   freeMorphism(M_tiny_gp_const_mutate_mutate_input);
}

Graph* tiny_gp_const_mutate_host = NULL;
int* tiny_gp_const_mutate_node_map = NULL;
MorphismPot* tiny_gp_const_mutate_pot = NULL;

static void tiny_gp_const_mutate_garbageCollect(void)
{
   tiny_gp_const_mutate_freeMorphisms();
   freePot(tiny_gp_const_mutate_pot);
}

bool tiny_gp_const_mutate_success = true;

int tiny_gp_const_mutate_execute(Graph* host_graph)
{
   tiny_gp_const_mutate_host = host_graph;
   tiny_gp_const_mutate_success = true;
   tiny_gp_const_mutate_pot = makeMorphismPot();
   emptyPot(tiny_gp_const_mutate_pot);
   M_tiny_gp_const_mutate_mutate_input = makeMorphism(3, 1, 5);

   /* Rule Call */
   emptyPot(tiny_gp_const_mutate_pot);
   fillpottiny_gp_const_mutate_mutate_input(tiny_gp_const_mutate_pot, M_tiny_gp_const_mutate_mutate_input);
   if(potSize(tiny_gp_const_mutate_pot) > 0){
      MorphismHolder *holder = drawFromPot(tiny_gp_const_mutate_pot);
      duplicateMorphism(holder->morphism, M_tiny_gp_const_mutate_mutate_input, tiny_gp_const_mutate_host);
      freeMorphism(holder->morphism);
      free(holder);
      applytiny_gp_const_mutate_mutate_input(M_tiny_gp_const_mutate_mutate_input, false);
      tiny_gp_const_mutate_success = true;
   }
   else
   {
      printf("No output graph: rule tiny_gp_const_mutate_mutate_input not applicable.\n");
      tiny_gp_const_mutate_garbageCollect();
      return 0;
   }
   emptyPot(tiny_gp_const_mutate_pot);
   tiny_gp_const_mutate_garbageCollect();
   return 0;
}


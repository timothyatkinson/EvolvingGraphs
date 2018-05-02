#include <time.h>
#include "common.h"
#include "debug.h"
#include "graph.h"
#include "graphStacks.h"
#include "parser.h"
#include "morphism.h"

#include "a_node_pickNode.h"
Morphism *M_a_node_pickNode = NULL;
#include "a_node_mutateNode.h"
Morphism *M_a_node_mutateNode = NULL;

static void a_node_freeMorphisms(void)
{
   freeMorphism(M_a_node_pickNode);
   freeMorphism(M_a_node_mutateNode);
}

Graph* a_node_host = NULL;
int* a_node_node_map = NULL;
MorphismPot* a_node_pot = NULL;

static void a_node_garbageCollect(void)
{
   a_node_freeMorphisms();
   freePot(a_node_pot);
}

bool a_node_success = true;

int a_node_execute(Graph* host_graph)
{
   a_node_host = host_graph;
   a_node_success = true;
   a_node_pot = makeMorphismPot();
   emptyPot(a_node_pot);
   M_a_node_pickNode = makeMorphism(1, 0, 1);
   M_a_node_mutateNode = makeMorphism(2, 0, 3);

   /* Rule Call */
   emptyPot(a_node_pot);
   fillpota_node_pickNode(a_node_pot, M_a_node_pickNode);
   if(potSize(a_node_pot) > 0){
      MorphismHolder *holder = drawFromPot(a_node_pot);
      duplicateMorphism(holder->morphism, M_a_node_pickNode, a_node_host);
      freeMorphism(holder->morphism);
      free(holder);
      applya_node_pickNode(M_a_node_pickNode, false);
      a_node_success = true;
   }
   else
   {
      printf("No output graph: rule a_node_pickNode not applicable.\n");
      a_node_garbageCollect();
      return 0;
   }
   emptyPot(a_node_pot);
   /* Rule Call */
   emptyPot(a_node_pot);
   fillpota_node_mutateNode(a_node_pot, M_a_node_mutateNode);
   if(potSize(a_node_pot) > 0){
      MorphismHolder *holder = drawFromPot(a_node_pot);
      duplicateMorphism(holder->morphism, M_a_node_mutateNode, a_node_host);
      freeMorphism(holder->morphism);
      free(holder);
      applya_node_mutateNode(M_a_node_mutateNode, false);
      a_node_success = true;
   }
   else
   {
      printf("No output graph: rule a_node_mutateNode not applicable.\n");
      a_node_garbageCollect();
      return 0;
   }
   emptyPot(a_node_pot);
   a_node_garbageCollect();
   return 0;
}


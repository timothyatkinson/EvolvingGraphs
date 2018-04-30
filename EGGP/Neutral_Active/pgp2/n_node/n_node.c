#include <time.h>
#include "common.h"
#include "debug.h"
#include "graph.h"
#include "graphStacks.h"
#include "parser.h"
#include "morphism.h"

#include "n_node_initActiveNode.h"
Morphism *M_n_node_initActiveNode = NULL;
#include "n_node_outActive.h"
Morphism *M_n_node_outActive = NULL;
#include "n_node_propActive.h"
Morphism *M_n_node_propActive = NULL;
#include "n_node_removeActiveEdge.h"
Morphism *M_n_node_removeActiveEdge = NULL;
#include "n_node_removeActive.h"
Morphism *M_n_node_removeActive = NULL;
#include "n_node_pickNode.h"
Morphism *M_n_node_pickNode = NULL;
#include "n_node_mutateNode.h"
Morphism *M_n_node_mutateNode = NULL;

static void n_node_freeMorphisms(void)
{
   freeMorphism(M_n_node_initActiveNode);
   freeMorphism(M_n_node_outActive);
   freeMorphism(M_n_node_propActive);
   freeMorphism(M_n_node_removeActiveEdge);
   freeMorphism(M_n_node_removeActive);
   freeMorphism(M_n_node_pickNode);
   freeMorphism(M_n_node_mutateNode);
}

Graph* n_node_host = NULL;
int* n_node_node_map = NULL;
MorphismPot* n_node_pot = NULL;

static void n_node_garbageCollect(void)
{
   n_node_freeMorphisms();
   freePot(n_node_pot);
}

bool n_node_success = true;

int n_node_execute(Graph* host_graph)
{
   n_node_host = host_graph;
   n_node_success = true;
   n_node_pot = makeMorphismPot();
   emptyPot(n_node_pot);
   M_n_node_initActiveNode = makeMorphism(1, 0, 1);
   M_n_node_outActive = makeMorphism(2, 0, 1);
   M_n_node_propActive = makeMorphism(3, 1, 3);
   M_n_node_removeActiveEdge = makeMorphism(2, 1, 1);
   M_n_node_removeActive = makeMorphism(1, 0, 0);
   M_n_node_pickNode = makeMorphism(2, 0, 1);
   M_n_node_mutateNode = makeMorphism(2, 0, 3);

   /* Rule Call */
   if(matchn_node_initActiveNode(M_n_node_initActiveNode))
   {
      applyn_node_initActiveNode(M_n_node_initActiveNode, false);
      n_node_success = true;
   }
   else
   {
      printf("No output graph: rule n_node_initActiveNode not applicable.\n");
      n_node_garbageCollect();
      return 0;
   }
   /* Loop Statement */
   while(n_node_success)
   {
      /* Rule Call */
      if(matchn_node_outActive(M_n_node_outActive))
      {
         applyn_node_outActive(M_n_node_outActive, false);
         n_node_success = true;
      }
      else
      {
         n_node_success = false;
      }
   }
   n_node_success = true;
   /* Loop Statement */
   while(n_node_success)
   {
      /* Rule Call */
      if(matchn_node_propActive(M_n_node_propActive))
      {
         applyn_node_propActive(M_n_node_propActive, false);
         n_node_success = true;
      }
      else
      {
         n_node_success = false;
      }
   }
   n_node_success = true;
   /* Rule Call */
   emptyPot(n_node_pot);
   fillpotn_node_pickNode(n_node_pot, M_n_node_pickNode);
   if(potSize(n_node_pot) > 0){
      MorphismHolder *holder = drawFromPot(n_node_pot);
      duplicateMorphism(holder->morphism, M_n_node_pickNode, n_node_host);
      freeMorphism(holder->morphism);
      free(holder);
      applyn_node_pickNode(M_n_node_pickNode, false);
      n_node_success = true;
   }
   else
   {
      printf("No output graph: rule n_node_pickNode not applicable.\n");
      n_node_garbageCollect();
      return 0;
   }
   emptyPot(n_node_pot);
   /* Rule Call */
   emptyPot(n_node_pot);
   fillpotn_node_mutateNode(n_node_pot, M_n_node_mutateNode);
   if(potSize(n_node_pot) > 0){
      MorphismHolder *holder = drawFromPot(n_node_pot);
      duplicateMorphism(holder->morphism, M_n_node_mutateNode, n_node_host);
      freeMorphism(holder->morphism);
      free(holder);
      applyn_node_mutateNode(M_n_node_mutateNode, false);
      n_node_success = true;
   }
   else
   {
      printf("No output graph: rule n_node_mutateNode not applicable.\n");
      n_node_garbageCollect();
      return 0;
   }
   emptyPot(n_node_pot);
   /* Loop Statement */
   while(n_node_success)
   {
      /* Rule Call */
      if(matchn_node_removeActiveEdge(M_n_node_removeActiveEdge))
      {
         applyn_node_removeActiveEdge(M_n_node_removeActiveEdge, false);
         n_node_success = true;
      }
      else
      {
         n_node_success = false;
      }
   }
   n_node_success = true;
   /* Rule Call */
   if(matchn_node_removeActive(M_n_node_removeActive))
   {
      applyn_node_removeActive(M_n_node_removeActive, false);
      n_node_success = true;
   }
   else
   {
      printf("No output graph: rule n_node_removeActive not applicable.\n");
      n_node_garbageCollect();
      return 0;
   }
   n_node_garbageCollect();
   return 0;
}


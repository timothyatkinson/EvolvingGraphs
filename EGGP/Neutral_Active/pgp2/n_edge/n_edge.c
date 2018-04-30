#include <time.h>
#include "common.h"
#include "debug.h"
#include "graph.h"
#include "graphStacks.h"
#include "parser.h"
#include "morphism.h"

#include "n_edge_initActiveNode.h"
Morphism *M_n_edge_initActiveNode = NULL;
#include "n_edge_outActive.h"
Morphism *M_n_edge_outActive = NULL;
#include "n_edge_propActive.h"
Morphism *M_n_edge_propActive = NULL;
#include "n_edge_removeActiveEdge.h"
Morphism *M_n_edge_removeActiveEdge = NULL;
#include "n_edge_removeActive.h"
Morphism *M_n_edge_removeActive = NULL;
#include "n_edge_pickEdge.h"
Morphism *M_n_edge_pickEdge = NULL;
#include "n_edge_markOutputs.h"
Morphism *M_n_edge_markOutputs = NULL;
#include "n_edge_pickNewTarget.h"
Morphism *M_n_edge_pickNewTarget = NULL;
#include "n_edge_mutateEdge.h"
Morphism *M_n_edge_mutateEdge = NULL;
#include "n_edge_unmarkOutputs.h"
Morphism *M_n_edge_unmarkOutputs = NULL;

static void n_edge_freeMorphisms(void)
{
   freeMorphism(M_n_edge_initActiveNode);
   freeMorphism(M_n_edge_outActive);
   freeMorphism(M_n_edge_propActive);
   freeMorphism(M_n_edge_removeActiveEdge);
   freeMorphism(M_n_edge_removeActive);
   freeMorphism(M_n_edge_pickEdge);
   freeMorphism(M_n_edge_markOutputs);
   freeMorphism(M_n_edge_pickNewTarget);
   freeMorphism(M_n_edge_mutateEdge);
   freeMorphism(M_n_edge_unmarkOutputs);
}

Graph* n_edge_host = NULL;
int* n_edge_node_map = NULL;
MorphismPot* n_edge_pot = NULL;

static void n_edge_garbageCollect(void)
{
   n_edge_freeMorphisms();
   freePot(n_edge_pot);
}

bool n_edge_success = true;

int n_edge_execute(Graph* host_graph)
{
   n_edge_host = host_graph;
   n_edge_success = true;
   n_edge_pot = makeMorphismPot();
   emptyPot(n_edge_pot);
   M_n_edge_initActiveNode = makeMorphism(1, 0, 1);
   M_n_edge_outActive = makeMorphism(2, 0, 1);
   M_n_edge_propActive = makeMorphism(3, 1, 3);
   M_n_edge_removeActiveEdge = makeMorphism(2, 1, 1);
   M_n_edge_removeActive = makeMorphism(1, 0, 0);
   M_n_edge_pickEdge = makeMorphism(3, 1, 3);
   M_n_edge_markOutputs = makeMorphism(2, 1, 3);
   M_n_edge_pickNewTarget = makeMorphism(1, 0, 2);
   M_n_edge_mutateEdge = makeMorphism(3, 1, 5);
   M_n_edge_unmarkOutputs = makeMorphism(1, 0, 1);

   /* Rule Call */
   if(matchn_edge_initActiveNode(M_n_edge_initActiveNode))
   {
      applyn_edge_initActiveNode(M_n_edge_initActiveNode, false);
      n_edge_success = true;
   }
   else
   {
      printf("No output graph: rule n_edge_initActiveNode not applicable.\n");
      n_edge_garbageCollect();
      return 0;
   }
   /* Loop Statement */
   while(n_edge_success)
   {
      /* Rule Call */
      if(matchn_edge_outActive(M_n_edge_outActive))
      {
         applyn_edge_outActive(M_n_edge_outActive, false);
         n_edge_success = true;
      }
      else
      {
         n_edge_success = false;
      }
   }
   n_edge_success = true;
   /* Loop Statement */
   while(n_edge_success)
   {
      /* Rule Call */
      if(matchn_edge_propActive(M_n_edge_propActive))
      {
         applyn_edge_propActive(M_n_edge_propActive, false);
         n_edge_success = true;
      }
      else
      {
         n_edge_success = false;
      }
   }
   n_edge_success = true;
   /* Try Statement */
   /* Condition */
   int restore_point0 = graph_change_stack == NULL ? 0 : topOfGraphChangeStack();
   do
   {
      /* Rule Call */
      emptyPot(n_edge_pot);
      fillpotn_edge_pickEdge(n_edge_pot, M_n_edge_pickEdge);
      if(potSize(n_edge_pot) > 0){
         MorphismHolder *holder = drawFromPot(n_edge_pot);
         duplicateMorphism(holder->morphism, M_n_edge_pickEdge, n_edge_host);
         freeMorphism(holder->morphism);
         free(holder);
         applyn_edge_pickEdge(M_n_edge_pickEdge, true);
         n_edge_success = true;
      }
      else
      {
         n_edge_success = false;
         break;
      }
      emptyPot(n_edge_pot);
      /* Loop Statement */
      while(n_edge_success)
      {
         /* Rule Call */
         if(matchn_edge_markOutputs(M_n_edge_markOutputs))
         {
            applyn_edge_markOutputs(M_n_edge_markOutputs, true);
            n_edge_success = true;
         }
         else
         {
            n_edge_success = false;
         }
      }
      n_edge_success = true;
      /* Rule Call */
      emptyPot(n_edge_pot);
      fillpotn_edge_mutateEdge(n_edge_pot, M_n_edge_mutateEdge);
      if(potSize(n_edge_pot) > 0){
         MorphismHolder *holder = drawFromPot(n_edge_pot);
         duplicateMorphism(holder->morphism, M_n_edge_mutateEdge, n_edge_host);
         freeMorphism(holder->morphism);
         free(holder);
         applyn_edge_mutateEdge(M_n_edge_mutateEdge, true);
         n_edge_success = true;
      }
      else
      {
         n_edge_success = false;
         break;
      }
      emptyPot(n_edge_pot);
      /* Loop Statement */
      while(n_edge_success)
      {
         /* Rule Call */
         if(matchn_edge_unmarkOutputs(M_n_edge_unmarkOutputs))
         {
            applyn_edge_unmarkOutputs(M_n_edge_unmarkOutputs, true);
            n_edge_success = true;
         }
         else
         {
            n_edge_success = false;
         }
      }
      n_edge_success = true;
   } while(false);

   /* Then Branch */
   if(n_edge_success)
   {
      discardChanges(restore_point0);
      /* Skip Statement */
      n_edge_success = true;
   }
   /* Else Branch */
   else
   {
      undoChanges(n_edge_host, restore_point0);
      n_edge_success = true;
      /* Skip Statement */
      n_edge_success = true;
   }
   /* Loop Statement */
   while(n_edge_success)
   {
      /* Rule Call */
      if(matchn_edge_removeActiveEdge(M_n_edge_removeActiveEdge))
      {
         applyn_edge_removeActiveEdge(M_n_edge_removeActiveEdge, false);
         n_edge_success = true;
      }
      else
      {
         n_edge_success = false;
      }
   }
   n_edge_success = true;
   /* Rule Call */
   if(matchn_edge_removeActive(M_n_edge_removeActive))
   {
      applyn_edge_removeActive(M_n_edge_removeActive, false);
      n_edge_success = true;
   }
   else
   {
      printf("No output graph: rule n_edge_removeActive not applicable.\n");
      n_edge_garbageCollect();
      return 0;
   }
   n_edge_garbageCollect();
   return 0;
}


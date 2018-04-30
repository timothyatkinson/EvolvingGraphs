#include <time.h>
#include "common.h"
#include "debug.h"
#include "graph.h"
#include "graphStacks.h"
#include "parser.h"
#include "morphism.h"

#include "a_edge_initActiveNode.h"
Morphism *M_a_edge_initActiveNode = NULL;
#include "a_edge_outActive.h"
Morphism *M_a_edge_outActive = NULL;
#include "a_edge_propActive.h"
Morphism *M_a_edge_propActive = NULL;
#include "a_edge_removeActiveEdge.h"
Morphism *M_a_edge_removeActiveEdge = NULL;
#include "a_edge_removeActive.h"
Morphism *M_a_edge_removeActive = NULL;
#include "a_edge_pickEdge.h"
Morphism *M_a_edge_pickEdge = NULL;
#include "a_edge_markOutputs.h"
Morphism *M_a_edge_markOutputs = NULL;
#include "a_edge_pickNewTarget.h"
Morphism *M_a_edge_pickNewTarget = NULL;
#include "a_edge_mutateEdge.h"
Morphism *M_a_edge_mutateEdge = NULL;
#include "a_edge_unmarkOutputs.h"
Morphism *M_a_edge_unmarkOutputs = NULL;

static void a_edge_freeMorphisms(void)
{
   freeMorphism(M_a_edge_initActiveNode);
   freeMorphism(M_a_edge_outActive);
   freeMorphism(M_a_edge_propActive);
   freeMorphism(M_a_edge_removeActiveEdge);
   freeMorphism(M_a_edge_removeActive);
   freeMorphism(M_a_edge_pickEdge);
   freeMorphism(M_a_edge_markOutputs);
   freeMorphism(M_a_edge_pickNewTarget);
   freeMorphism(M_a_edge_mutateEdge);
   freeMorphism(M_a_edge_unmarkOutputs);
}

Graph* a_edge_host = NULL;
int* a_edge_node_map = NULL;
MorphismPot* a_edge_pot = NULL;

static void a_edge_garbageCollect(void)
{
   a_edge_freeMorphisms();
   freePot(a_edge_pot);
}

bool a_edge_success = true;

int a_edge_execute(Graph* host_graph)
{
   a_edge_host = host_graph;
   a_edge_success = true;
   a_edge_pot = makeMorphismPot();
   emptyPot(a_edge_pot);
   M_a_edge_initActiveNode = makeMorphism(1, 0, 1);
   M_a_edge_outActive = makeMorphism(2, 0, 1);
   M_a_edge_propActive = makeMorphism(3, 1, 3);
   M_a_edge_removeActiveEdge = makeMorphism(2, 1, 1);
   M_a_edge_removeActive = makeMorphism(1, 0, 0);
   M_a_edge_pickEdge = makeMorphism(3, 1, 3);
   M_a_edge_markOutputs = makeMorphism(2, 1, 3);
   M_a_edge_pickNewTarget = makeMorphism(1, 0, 2);
   M_a_edge_mutateEdge = makeMorphism(3, 1, 5);
   M_a_edge_unmarkOutputs = makeMorphism(1, 0, 1);

   /* Rule Call */
   if(matcha_edge_initActiveNode(M_a_edge_initActiveNode))
   {
      applya_edge_initActiveNode(M_a_edge_initActiveNode, false);
      a_edge_success = true;
   }
   else
   {
      printf("No output graph: rule a_edge_initActiveNode not applicable.\n");
      a_edge_garbageCollect();
      return 0;
   }
   /* Loop Statement */
   while(a_edge_success)
   {
      /* Rule Call */
      if(matcha_edge_outActive(M_a_edge_outActive))
      {
         applya_edge_outActive(M_a_edge_outActive, false);
         a_edge_success = true;
      }
      else
      {
         a_edge_success = false;
      }
   }
   a_edge_success = true;
   /* Loop Statement */
   while(a_edge_success)
   {
      /* Rule Call */
      if(matcha_edge_propActive(M_a_edge_propActive))
      {
         applya_edge_propActive(M_a_edge_propActive, false);
         a_edge_success = true;
      }
      else
      {
         a_edge_success = false;
      }
   }
   a_edge_success = true;
   /* Try Statement */
   /* Condition */
   int restore_point0 = graph_change_stack == NULL ? 0 : topOfGraphChangeStack();
   do
   {
      /* Rule Call */
      emptyPot(a_edge_pot);
      fillpota_edge_pickEdge(a_edge_pot, M_a_edge_pickEdge);
      if(potSize(a_edge_pot) > 0){
         MorphismHolder *holder = drawFromPot(a_edge_pot);
         duplicateMorphism(holder->morphism, M_a_edge_pickEdge, a_edge_host);
         freeMorphism(holder->morphism);
         free(holder);
         applya_edge_pickEdge(M_a_edge_pickEdge, true);
         a_edge_success = true;
      }
      else
      {
         a_edge_success = false;
         break;
      }
      emptyPot(a_edge_pot);
      /* Loop Statement */
      while(a_edge_success)
      {
         /* Rule Call */
         if(matcha_edge_markOutputs(M_a_edge_markOutputs))
         {
            applya_edge_markOutputs(M_a_edge_markOutputs, true);
            a_edge_success = true;
         }
         else
         {
            a_edge_success = false;
         }
      }
      a_edge_success = true;
      /* Rule Call */
      emptyPot(a_edge_pot);
      fillpota_edge_mutateEdge(a_edge_pot, M_a_edge_mutateEdge);
      if(potSize(a_edge_pot) > 0){
         MorphismHolder *holder = drawFromPot(a_edge_pot);
         duplicateMorphism(holder->morphism, M_a_edge_mutateEdge, a_edge_host);
         freeMorphism(holder->morphism);
         free(holder);
         applya_edge_mutateEdge(M_a_edge_mutateEdge, true);
         a_edge_success = true;
      }
      else
      {
         a_edge_success = false;
         break;
      }
      emptyPot(a_edge_pot);
      /* Loop Statement */
      while(a_edge_success)
      {
         /* Rule Call */
         if(matcha_edge_unmarkOutputs(M_a_edge_unmarkOutputs))
         {
            applya_edge_unmarkOutputs(M_a_edge_unmarkOutputs, true);
            a_edge_success = true;
         }
         else
         {
            a_edge_success = false;
         }
      }
      a_edge_success = true;
   } while(false);

   /* Then Branch */
   if(a_edge_success)
   {
      discardChanges(restore_point0);
      /* Skip Statement */
      a_edge_success = true;
   }
   /* Else Branch */
   else
   {
      undoChanges(a_edge_host, restore_point0);
      a_edge_success = true;
      /* Skip Statement */
      a_edge_success = true;
   }
   /* Loop Statement */
   while(a_edge_success)
   {
      /* Rule Call */
      if(matcha_edge_removeActiveEdge(M_a_edge_removeActiveEdge))
      {
         applya_edge_removeActiveEdge(M_a_edge_removeActiveEdge, false);
         a_edge_success = true;
      }
      else
      {
         a_edge_success = false;
      }
   }
   a_edge_success = true;
   /* Rule Call */
   if(matcha_edge_removeActive(M_a_edge_removeActive))
   {
      applya_edge_removeActive(M_a_edge_removeActive, false);
      a_edge_success = true;
   }
   else
   {
      printf("No output graph: rule a_edge_removeActive not applicable.\n");
      a_edge_garbageCollect();
      return 0;
   }
   a_edge_garbageCollect();
   return 0;
}


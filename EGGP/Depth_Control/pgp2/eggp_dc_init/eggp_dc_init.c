#include <time.h>
#include "common.h"
#include "debug.h"
#include "graph.h"
#include "graphStacks.h"
#include "parser.h"
#include "morphism.h"

#include "eggp_dc_init_initNodeCounter.h"
Morphism *M_eggp_dc_init_initNodeCounter = NULL;
#include "eggp_dc_init_addNode.h"
Morphism *M_eggp_dc_init_addNode = NULL;
#include "eggp_dc_init_addEdgeToArity.h"
Morphism *M_eggp_dc_init_addEdgeToArity = NULL;
#include "eggp_dc_init_updateDepth.h"
Morphism *M_eggp_dc_init_updateDepth = NULL;
#include "eggp_dc_init_decolourNode.h"
Morphism *M_eggp_dc_init_decolourNode = NULL;
#include "eggp_dc_init_connectOutput.h"
Morphism *M_eggp_dc_init_connectOutput = NULL;
#include "eggp_dc_init_deleteNodeCounter.h"
Morphism *M_eggp_dc_init_deleteNodeCounter = NULL;
#include "eggp_dc_init_removeDepth.h"
Morphism *M_eggp_dc_init_removeDepth = NULL;

static void eggp_dc_init_freeMorphisms(void)
{
   freeMorphism(M_eggp_dc_init_initNodeCounter);
   freeMorphism(M_eggp_dc_init_addNode);
   freeMorphism(M_eggp_dc_init_addEdgeToArity);
   freeMorphism(M_eggp_dc_init_updateDepth);
   freeMorphism(M_eggp_dc_init_decolourNode);
   freeMorphism(M_eggp_dc_init_connectOutput);
   freeMorphism(M_eggp_dc_init_deleteNodeCounter);
   freeMorphism(M_eggp_dc_init_removeDepth);
}

Graph* eggp_dc_init_host = NULL;
int* eggp_dc_init_node_map = NULL;
MorphismPot* eggp_dc_init_pot = NULL;

static void eggp_dc_init_garbageCollect(void)
{
   eggp_dc_init_freeMorphisms();
   freePot(eggp_dc_init_pot);
}

bool eggp_dc_init_success = true;

int eggp_dc_init_execute(Graph* host_graph)
{
   eggp_dc_init_host = host_graph;
   eggp_dc_init_success = true;
   eggp_dc_init_pot = makeMorphismPot();
   emptyPot(eggp_dc_init_pot);
   M_eggp_dc_init_initNodeCounter = makeMorphism(1, 0, 1);
   M_eggp_dc_init_addNode = makeMorphism(2, 0, 3);
   M_eggp_dc_init_addEdgeToArity = makeMorphism(4, 0, 7);
   M_eggp_dc_init_updateDepth = makeMorphism(2, 1, 7);
   M_eggp_dc_init_decolourNode = makeMorphism(1, 0, 1);
   M_eggp_dc_init_connectOutput = makeMorphism(2, 0, 3);
   M_eggp_dc_init_deleteNodeCounter = makeMorphism(1, 0, 1);
   M_eggp_dc_init_removeDepth = makeMorphism(1, 0, 3);

   /* Rule Call */
   if(matcheggp_dc_init_initNodeCounter(M_eggp_dc_init_initNodeCounter))
   {
      applyeggp_dc_init_initNodeCounter(M_eggp_dc_init_initNodeCounter, false);
      eggp_dc_init_success = true;
   }
   else
   {
      printf("No output graph: rule eggp_dc_init_initNodeCounter not applicable.\n");
      eggp_dc_init_garbageCollect();
      return 0;
   }
   /* Loop Statement */
   int restore_point0 = graph_change_stack == NULL ? 0 : topOfGraphChangeStack();
   while(eggp_dc_init_success)
   {
      /* Rule Call */
      emptyPot(eggp_dc_init_pot);
      fillpoteggp_dc_init_addNode(eggp_dc_init_pot, M_eggp_dc_init_addNode);
      if(potSize(eggp_dc_init_pot) > 0){
         MorphismHolder *holder = drawFromPot(eggp_dc_init_pot);
         duplicateMorphism(holder->morphism, M_eggp_dc_init_addNode, eggp_dc_init_host);
         freeMorphism(holder->morphism);
         free(holder);
         applyeggp_dc_init_addNode(M_eggp_dc_init_addNode, true);
         eggp_dc_init_success = true;
      }
      else
      {
         eggp_dc_init_success = false;
         undoChanges(eggp_dc_init_host, restore_point0);
      }
      emptyPot(eggp_dc_init_pot);
      if(!eggp_dc_init_success) break;

      /* Loop Statement */
      while(eggp_dc_init_success)
      {
         /* Rule Call */
         emptyPot(eggp_dc_init_pot);
         fillpoteggp_dc_init_addEdgeToArity(eggp_dc_init_pot, M_eggp_dc_init_addEdgeToArity);
         if(potSize(eggp_dc_init_pot) > 0){
            MorphismHolder *holder = drawFromPot(eggp_dc_init_pot);
            duplicateMorphism(holder->morphism, M_eggp_dc_init_addEdgeToArity, eggp_dc_init_host);
            freeMorphism(holder->morphism);
            free(holder);
            applyeggp_dc_init_addEdgeToArity(M_eggp_dc_init_addEdgeToArity, true);
            eggp_dc_init_success = true;
         }
         else
         {
            eggp_dc_init_success = false;
         }
         emptyPot(eggp_dc_init_pot);
      }
      eggp_dc_init_success = true;
      if(!eggp_dc_init_success) break;

      /* Loop Statement */
      while(eggp_dc_init_success)
      {
         /* Rule Call */
         if(matcheggp_dc_init_updateDepth(M_eggp_dc_init_updateDepth))
         {
            applyeggp_dc_init_updateDepth(M_eggp_dc_init_updateDepth, true);
            eggp_dc_init_success = true;
         }
         else
         {
            eggp_dc_init_success = false;
         }
      }
      eggp_dc_init_success = true;
      if(!eggp_dc_init_success) break;

      /* Rule Call */
      if(matcheggp_dc_init_decolourNode(M_eggp_dc_init_decolourNode))
      {
         applyeggp_dc_init_decolourNode(M_eggp_dc_init_decolourNode, true);
         eggp_dc_init_success = true;
      }
      else
      {
         eggp_dc_init_success = false;
         undoChanges(eggp_dc_init_host, restore_point0);
      }
      /* Graph changes from loop body may not have been used.
         Discard them so that future graph roll backs are uncorrupted. */
      if(eggp_dc_init_success) discardChanges(restore_point0);
   }
   eggp_dc_init_success = true;
   /* Loop Statement */
   while(eggp_dc_init_success)
   {
      /* Rule Call */
      emptyPot(eggp_dc_init_pot);
      fillpoteggp_dc_init_connectOutput(eggp_dc_init_pot, M_eggp_dc_init_connectOutput);
      if(potSize(eggp_dc_init_pot) > 0){
         MorphismHolder *holder = drawFromPot(eggp_dc_init_pot);
         duplicateMorphism(holder->morphism, M_eggp_dc_init_connectOutput, eggp_dc_init_host);
         freeMorphism(holder->morphism);
         free(holder);
         applyeggp_dc_init_connectOutput(M_eggp_dc_init_connectOutput, false);
         eggp_dc_init_success = true;
      }
      else
      {
         eggp_dc_init_success = false;
      }
      emptyPot(eggp_dc_init_pot);
   }
   eggp_dc_init_success = true;
   /* Loop Statement */
   while(eggp_dc_init_success)
   {
      /* Rule Call */
      if(matcheggp_dc_init_removeDepth(M_eggp_dc_init_removeDepth))
      {
         applyeggp_dc_init_removeDepth(M_eggp_dc_init_removeDepth, false);
         eggp_dc_init_success = true;
      }
      else
      {
         eggp_dc_init_success = false;
      }
   }
   eggp_dc_init_success = true;
   /* Loop Statement */
   while(eggp_dc_init_success)
   {
      /* Rule Call */
      if(matcheggp_dc_init_decolourNode(M_eggp_dc_init_decolourNode))
      {
         applyeggp_dc_init_decolourNode(M_eggp_dc_init_decolourNode, false);
         eggp_dc_init_success = true;
      }
      else
      {
         eggp_dc_init_success = false;
      }
   }
   eggp_dc_init_success = true;
   /* Rule Call */
   if(matcheggp_dc_init_deleteNodeCounter(M_eggp_dc_init_deleteNodeCounter))
   {
      applyeggp_dc_init_deleteNodeCounter(M_eggp_dc_init_deleteNodeCounter, false);
      eggp_dc_init_success = true;
   }
   else
   {
      printf("No output graph: rule eggp_dc_init_deleteNodeCounter not applicable.\n");
      eggp_dc_init_garbageCollect();
      return 0;
   }
   eggp_dc_init_garbageCollect();
   return 0;
}


#include <time.h>
#include "common.h"
#include "debug.h"
#include "graph.h"
#include "graphStacks.h"
#include "parser.h"
#include "morphism.h"

#include "eggp_dc_fy_pickNode.h"
Morphism *M_eggp_dc_fy_pickNode = NULL;
#include "eggp_dc_fy_mutateNode.h"
Morphism *M_eggp_dc_fy_mutateNode = NULL;
#include "eggp_dc_fy_markOutputsBlue.h"
Morphism *M_eggp_dc_fy_markOutputsBlue = NULL;
#include "eggp_dc_fy_markOutputsRed.h"
Morphism *M_eggp_dc_fy_markOutputsRed = NULL;
#include "eggp_dc_fy_markDepth.h"
Morphism *M_eggp_dc_fy_markDepth = NULL;
#include "eggp_dc_fy_addEdgeToArity.h"
Morphism *M_eggp_dc_fy_addEdgeToArity = NULL;
#include "eggp_dc_fy_deleteEdgeToArity.h"
Morphism *M_eggp_dc_fy_deleteEdgeToArity = NULL;
#include "eggp_dc_fy_resetArityCounter.h"
Morphism *M_eggp_dc_fy_resetArityCounter = NULL;
#include "eggp_dc_fy_bucketEdge.h"
Morphism *M_eggp_dc_fy_bucketEdge = NULL;
#include "eggp_dc_fy_readdEdge.h"
Morphism *M_eggp_dc_fy_readdEdge = NULL;
#include "eggp_dc_fy_deleteArityC.h"
Morphism *M_eggp_dc_fy_deleteArityC = NULL;
#include "eggp_dc_fy_unmarkBlue.h"
Morphism *M_eggp_dc_fy_unmarkBlue = NULL;
#include "eggp_dc_fy_unmarkRed.h"
Morphism *M_eggp_dc_fy_unmarkRed = NULL;

static void eggp_dc_fy_freeMorphisms(void)
{
   freeMorphism(M_eggp_dc_fy_pickNode);
   freeMorphism(M_eggp_dc_fy_mutateNode);
   freeMorphism(M_eggp_dc_fy_markOutputsBlue);
   freeMorphism(M_eggp_dc_fy_markOutputsRed);
   freeMorphism(M_eggp_dc_fy_markDepth);
   freeMorphism(M_eggp_dc_fy_addEdgeToArity);
   freeMorphism(M_eggp_dc_fy_deleteEdgeToArity);
   freeMorphism(M_eggp_dc_fy_resetArityCounter);
   freeMorphism(M_eggp_dc_fy_bucketEdge);
   freeMorphism(M_eggp_dc_fy_readdEdge);
   freeMorphism(M_eggp_dc_fy_deleteArityC);
   freeMorphism(M_eggp_dc_fy_unmarkBlue);
   freeMorphism(M_eggp_dc_fy_unmarkRed);
}

Graph* eggp_dc_fy_host = NULL;
int* eggp_dc_fy_node_map = NULL;
MorphismPot* eggp_dc_fy_pot = NULL;

static void eggp_dc_fy_garbageCollect(void)
{
   eggp_dc_fy_freeMorphisms();
   freePot(eggp_dc_fy_pot);
}

bool eggp_dc_fy_success = true;

int eggp_dc_fy_execute(Graph* host_graph)
{
   eggp_dc_fy_host = host_graph;
   eggp_dc_fy_success = true;
   eggp_dc_fy_pot = makeMorphismPot();
   emptyPot(eggp_dc_fy_pot);
   M_eggp_dc_fy_pickNode = makeMorphism(1, 0, 2);
   M_eggp_dc_fy_mutateNode = makeMorphism(2, 0, 4);
   M_eggp_dc_fy_markOutputsBlue = makeMorphism(2, 1, 3);
   M_eggp_dc_fy_markOutputsRed = makeMorphism(2, 1, 3);
   M_eggp_dc_fy_markDepth = makeMorphism(3, 0, 11);
   M_eggp_dc_fy_addEdgeToArity = makeMorphism(4, 0, 6);
   M_eggp_dc_fy_deleteEdgeToArity = makeMorphism(4, 1, 7);
   M_eggp_dc_fy_resetArityCounter = makeMorphism(1, 0, 1);
   M_eggp_dc_fy_bucketEdge = makeMorphism(2, 1, 3);
   M_eggp_dc_fy_readdEdge = makeMorphism(3, 1, 4);
   M_eggp_dc_fy_deleteArityC = makeMorphism(2, 0, 2);
   M_eggp_dc_fy_unmarkBlue = makeMorphism(1, 0, 1);
   M_eggp_dc_fy_unmarkRed = makeMorphism(1, 0, 1);

   /* Rule Call */
   emptyPot(eggp_dc_fy_pot);
   fillpoteggp_dc_fy_pickNode(eggp_dc_fy_pot, M_eggp_dc_fy_pickNode);
   if(potSize(eggp_dc_fy_pot) > 0){
      MorphismHolder *holder = drawFromPot(eggp_dc_fy_pot);
      duplicateMorphism(holder->morphism, M_eggp_dc_fy_pickNode, eggp_dc_fy_host);
      freeMorphism(holder->morphism);
      free(holder);
      applyeggp_dc_fy_pickNode(M_eggp_dc_fy_pickNode, false);
      eggp_dc_fy_success = true;
   }
   else
   {
      printf("No output graph: rule eggp_dc_fy_pickNode not applicable.\n");
      eggp_dc_fy_garbageCollect();
      return 0;
   }
   emptyPot(eggp_dc_fy_pot);
   /* Rule Call */
   emptyPot(eggp_dc_fy_pot);
   fillpoteggp_dc_fy_mutateNode(eggp_dc_fy_pot, M_eggp_dc_fy_mutateNode);
   if(potSize(eggp_dc_fy_pot) > 0){
      MorphismHolder *holder = drawFromPot(eggp_dc_fy_pot);
      duplicateMorphism(holder->morphism, M_eggp_dc_fy_mutateNode, eggp_dc_fy_host);
      freeMorphism(holder->morphism);
      free(holder);
      applyeggp_dc_fy_mutateNode(M_eggp_dc_fy_mutateNode, false);
      eggp_dc_fy_success = true;
   }
   else
   {
      printf("No output graph: rule eggp_dc_fy_mutateNode not applicable.\n");
      eggp_dc_fy_garbageCollect();
      return 0;
   }
   emptyPot(eggp_dc_fy_pot);
   /* Loop Statement */
   while(eggp_dc_fy_success)
   {
      /* Rule Set Call */
      do
      {
         if(matcheggp_dc_fy_markOutputsBlue(M_eggp_dc_fy_markOutputsBlue))
         {
            applyeggp_dc_fy_markOutputsBlue(M_eggp_dc_fy_markOutputsBlue, false);
            eggp_dc_fy_success = true;
            break;
         }
         if(matcheggp_dc_fy_markOutputsRed(M_eggp_dc_fy_markOutputsRed))
         {
            applyeggp_dc_fy_markOutputsRed(M_eggp_dc_fy_markOutputsRed, false);
            eggp_dc_fy_success = true;
         }
         else
         {
            eggp_dc_fy_success = false;
         }
      } while(false);
   }
   eggp_dc_fy_success = true;
   /* Loop Statement */
   while(eggp_dc_fy_success)
   {
      /* Rule Call */
      if(matcheggp_dc_fy_markDepth(M_eggp_dc_fy_markDepth))
      {
         applyeggp_dc_fy_markDepth(M_eggp_dc_fy_markDepth, false);
         eggp_dc_fy_success = true;
      }
      else
      {
         eggp_dc_fy_success = false;
      }
   }
   eggp_dc_fy_success = true;
   /* Loop Statement */
   while(eggp_dc_fy_success)
   {
      /* Rule Set Call */
      do
      {
      bool valid[2];
      double weight[2];
      double totalWeight = 0.0;
      bool someValid = false;
      valid[0] = false;
      weight[0] = 1.000000;
      if(matcheggp_dc_fy_addEdgeToArity(M_eggp_dc_fy_addEdgeToArity)){
         valid[0] = true;
         totalWeight = totalWeight + weight[0];
         someValid = true;
      }
      initialiseMorphism(M_eggp_dc_fy_addEdgeToArity, eggp_dc_fy_host);
      valid[1] = false;
      weight[1] = 1.000000;
      if(matcheggp_dc_fy_deleteEdgeToArity(M_eggp_dc_fy_deleteEdgeToArity)){
         valid[1] = true;
         totalWeight = totalWeight + weight[1];
         someValid = true;
      }
      initialiseMorphism(M_eggp_dc_fy_deleteEdgeToArity, eggp_dc_fy_host);
      if (someValid){
         double r = ((double)rand() / (double)RAND_MAX);
         r = r * totalWeight;
         double sum = 0.0;
         if(valid[0]){
            sum = sum + weight[0];
            if(r <= sum){
               emptyPot(eggp_dc_fy_pot);
               fillpoteggp_dc_fy_addEdgeToArity(eggp_dc_fy_pot, M_eggp_dc_fy_addEdgeToArity);
               if(potSize(eggp_dc_fy_pot) > 0){
                  MorphismHolder *holder = drawFromPot(eggp_dc_fy_pot);
                  duplicateMorphism(holder->morphism, M_eggp_dc_fy_addEdgeToArity, eggp_dc_fy_host);
                  freeMorphism(holder->morphism);
                  free(holder);
                  applyeggp_dc_fy_addEdgeToArity(M_eggp_dc_fy_addEdgeToArity, false);
                  eggp_dc_fy_success = true;
                  break;
               }
               emptyPot(eggp_dc_fy_pot);
            }
         }
         if(valid[1]){
            sum = sum + weight[1];
            if(r <= sum && r > sum - weight[1]){
               emptyPot(eggp_dc_fy_pot);
               fillpoteggp_dc_fy_deleteEdgeToArity(eggp_dc_fy_pot, M_eggp_dc_fy_deleteEdgeToArity);
               if(potSize(eggp_dc_fy_pot) > 0){
                  MorphismHolder *holder = drawFromPot(eggp_dc_fy_pot);
                  duplicateMorphism(holder->morphism, M_eggp_dc_fy_deleteEdgeToArity, eggp_dc_fy_host);
                  freeMorphism(holder->morphism);
                  free(holder);
                  applyeggp_dc_fy_deleteEdgeToArity(M_eggp_dc_fy_deleteEdgeToArity, false);
                  eggp_dc_fy_success = true;
                  break;
               }
               emptyPot(eggp_dc_fy_pot);
            }
         }
      } else {
      eggp_dc_fy_success = false;
      }
      } while(false);
   }
   eggp_dc_fy_success = true;
   /* Loop Statement */
   while(eggp_dc_fy_success)
   {
      /* Rule Call */
      if(matcheggp_dc_fy_unmarkBlue(M_eggp_dc_fy_unmarkBlue))
      {
         applyeggp_dc_fy_unmarkBlue(M_eggp_dc_fy_unmarkBlue, false);
         eggp_dc_fy_success = true;
      }
      else
      {
         eggp_dc_fy_success = false;
      }
   }
   eggp_dc_fy_success = true;
   /* Rule Call */
   if(matcheggp_dc_fy_resetArityCounter(M_eggp_dc_fy_resetArityCounter))
   {
      applyeggp_dc_fy_resetArityCounter(M_eggp_dc_fy_resetArityCounter, false);
      eggp_dc_fy_success = true;
   }
   else
   {
      printf("No output graph: rule eggp_dc_fy_resetArityCounter not applicable.\n");
      eggp_dc_fy_garbageCollect();
      return 0;
   }
   /* Loop Statement */
   while(eggp_dc_fy_success)
   {
      /* Rule Call */
      if(matcheggp_dc_fy_bucketEdge(M_eggp_dc_fy_bucketEdge))
      {
         applyeggp_dc_fy_bucketEdge(M_eggp_dc_fy_bucketEdge, false);
         eggp_dc_fy_success = true;
      }
      else
      {
         eggp_dc_fy_success = false;
      }
   }
   eggp_dc_fy_success = true;
   /* Loop Statement */
   while(eggp_dc_fy_success)
   {
      /* Rule Call */
      emptyPot(eggp_dc_fy_pot);
      fillpoteggp_dc_fy_readdEdge(eggp_dc_fy_pot, M_eggp_dc_fy_readdEdge);
      if(potSize(eggp_dc_fy_pot) > 0){
         MorphismHolder *holder = drawFromPot(eggp_dc_fy_pot);
         duplicateMorphism(holder->morphism, M_eggp_dc_fy_readdEdge, eggp_dc_fy_host);
         freeMorphism(holder->morphism);
         free(holder);
         applyeggp_dc_fy_readdEdge(M_eggp_dc_fy_readdEdge, false);
         eggp_dc_fy_success = true;
      }
      else
      {
         eggp_dc_fy_success = false;
      }
      emptyPot(eggp_dc_fy_pot);
   }
   eggp_dc_fy_success = true;
   /* Rule Call */
   if(matcheggp_dc_fy_deleteArityC(M_eggp_dc_fy_deleteArityC))
   {
      applyeggp_dc_fy_deleteArityC(M_eggp_dc_fy_deleteArityC, false);
      eggp_dc_fy_success = true;
   }
   else
   {
      printf("No output graph: rule eggp_dc_fy_deleteArityC not applicable.\n");
      eggp_dc_fy_garbageCollect();
      return 0;
   }
   /* Loop Statement */
   while(eggp_dc_fy_success)
   {
      /* Rule Set Call */
      do
      {
         if(matcheggp_dc_fy_unmarkBlue(M_eggp_dc_fy_unmarkBlue))
         {
            applyeggp_dc_fy_unmarkBlue(M_eggp_dc_fy_unmarkBlue, false);
            eggp_dc_fy_success = true;
            break;
         }
         if(matcheggp_dc_fy_unmarkRed(M_eggp_dc_fy_unmarkRed))
         {
            applyeggp_dc_fy_unmarkRed(M_eggp_dc_fy_unmarkRed, false);
            eggp_dc_fy_success = true;
         }
         else
         {
            eggp_dc_fy_success = false;
         }
      } while(false);
   }
   eggp_dc_fy_success = true;
   eggp_dc_fy_garbageCollect();
   return 0;
}


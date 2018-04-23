#include <time.h>
#include "common.h"
#include "debug.h"
#include "graph.h"
#include "graphStacks.h"
#include "parser.h"
#include "morphism.h"

#include "eggp_mutate_node_shuffle_pickNode.h"
Morphism *M_eggp_mutate_node_shuffle_pickNode = NULL;
#include "eggp_mutate_node_shuffle_mutateNode.h"
Morphism *M_eggp_mutate_node_shuffle_mutateNode = NULL;
#include "eggp_mutate_node_shuffle_markOutputsBlue.h"
Morphism *M_eggp_mutate_node_shuffle_markOutputsBlue = NULL;
#include "eggp_mutate_node_shuffle_markOutputsRed.h"
Morphism *M_eggp_mutate_node_shuffle_markOutputsRed = NULL;
#include "eggp_mutate_node_shuffle_addEdgeToArity.h"
Morphism *M_eggp_mutate_node_shuffle_addEdgeToArity = NULL;
#include "eggp_mutate_node_shuffle_deleteEdgeToArity.h"
Morphism *M_eggp_mutate_node_shuffle_deleteEdgeToArity = NULL;
#include "eggp_mutate_node_shuffle_resetArityCounter.h"
Morphism *M_eggp_mutate_node_shuffle_resetArityCounter = NULL;
#include "eggp_mutate_node_shuffle_bucketEdge.h"
Morphism *M_eggp_mutate_node_shuffle_bucketEdge = NULL;
#include "eggp_mutate_node_shuffle_readdEdge.h"
Morphism *M_eggp_mutate_node_shuffle_readdEdge = NULL;
#include "eggp_mutate_node_shuffle_deleteArityC.h"
Morphism *M_eggp_mutate_node_shuffle_deleteArityC = NULL;
#include "eggp_mutate_node_shuffle_unmarkBlue.h"
Morphism *M_eggp_mutate_node_shuffle_unmarkBlue = NULL;
#include "eggp_mutate_node_shuffle_unmarkRed.h"
Morphism *M_eggp_mutate_node_shuffle_unmarkRed = NULL;

static void eggp_mutate_node_shuffle_freeMorphisms(void)
{
   freeMorphism(M_eggp_mutate_node_shuffle_pickNode);
   freeMorphism(M_eggp_mutate_node_shuffle_mutateNode);
   freeMorphism(M_eggp_mutate_node_shuffle_markOutputsBlue);
   freeMorphism(M_eggp_mutate_node_shuffle_markOutputsRed);
   freeMorphism(M_eggp_mutate_node_shuffle_addEdgeToArity);
   freeMorphism(M_eggp_mutate_node_shuffle_deleteEdgeToArity);
   freeMorphism(M_eggp_mutate_node_shuffle_resetArityCounter);
   freeMorphism(M_eggp_mutate_node_shuffle_bucketEdge);
   freeMorphism(M_eggp_mutate_node_shuffle_readdEdge);
   freeMorphism(M_eggp_mutate_node_shuffle_deleteArityC);
   freeMorphism(M_eggp_mutate_node_shuffle_unmarkBlue);
   freeMorphism(M_eggp_mutate_node_shuffle_unmarkRed);
}

Graph* eggp_mutate_node_shuffle_host = NULL;
int* eggp_mutate_node_shuffle_node_map = NULL;
MorphismPot* eggp_mutate_node_shuffle_pot = NULL;

static void eggp_mutate_node_shuffle_garbageCollect(void)
{
   eggp_mutate_node_shuffle_freeMorphisms();
   freePot(eggp_mutate_node_shuffle_pot);
}

bool eggp_mutate_node_shuffle_success = true;

int eggp_mutate_node_shuffle_execute(Graph* host_graph)
{
   eggp_mutate_node_shuffle_host = host_graph;
   eggp_mutate_node_shuffle_success = true;
   eggp_mutate_node_shuffle_pot = makeMorphismPot();
   emptyPot(eggp_mutate_node_shuffle_pot);
   M_eggp_mutate_node_shuffle_pickNode = makeMorphism(1, 0, 2);
   M_eggp_mutate_node_shuffle_mutateNode = makeMorphism(2, 0, 4);
   M_eggp_mutate_node_shuffle_markOutputsBlue = makeMorphism(2, 1, 3);
   M_eggp_mutate_node_shuffle_markOutputsRed = makeMorphism(2, 1, 3);
   M_eggp_mutate_node_shuffle_addEdgeToArity = makeMorphism(4, 0, 6);
   M_eggp_mutate_node_shuffle_deleteEdgeToArity = makeMorphism(4, 1, 7);
   M_eggp_mutate_node_shuffle_resetArityCounter = makeMorphism(1, 0, 1);
   M_eggp_mutate_node_shuffle_bucketEdge = makeMorphism(2, 1, 3);
   M_eggp_mutate_node_shuffle_readdEdge = makeMorphism(3, 1, 4);
   M_eggp_mutate_node_shuffle_deleteArityC = makeMorphism(2, 0, 2);
   M_eggp_mutate_node_shuffle_unmarkBlue = makeMorphism(1, 0, 1);
   M_eggp_mutate_node_shuffle_unmarkRed = makeMorphism(1, 0, 1);

   /* Rule Call */
   emptyPot(eggp_mutate_node_shuffle_pot);
   fillpoteggp_mutate_node_shuffle_pickNode(eggp_mutate_node_shuffle_pot, M_eggp_mutate_node_shuffle_pickNode);
   if(potSize(eggp_mutate_node_shuffle_pot) > 0){
      MorphismHolder *holder = drawFromPot(eggp_mutate_node_shuffle_pot);
      duplicateMorphism(holder->morphism, M_eggp_mutate_node_shuffle_pickNode, eggp_mutate_node_shuffle_host);
      freeMorphism(holder->morphism);
      free(holder);
      applyeggp_mutate_node_shuffle_pickNode(M_eggp_mutate_node_shuffle_pickNode, false);
      eggp_mutate_node_shuffle_success = true;
   }
   else
   {
      printf("No output graph: rule eggp_mutate_node_shuffle_pickNode not applicable.\n");
      eggp_mutate_node_shuffle_garbageCollect();
      return 0;
   }
   emptyPot(eggp_mutate_node_shuffle_pot);
   /* Rule Call */
   emptyPot(eggp_mutate_node_shuffle_pot);
   fillpoteggp_mutate_node_shuffle_mutateNode(eggp_mutate_node_shuffle_pot, M_eggp_mutate_node_shuffle_mutateNode);
   if(potSize(eggp_mutate_node_shuffle_pot) > 0){
      MorphismHolder *holder = drawFromPot(eggp_mutate_node_shuffle_pot);
      duplicateMorphism(holder->morphism, M_eggp_mutate_node_shuffle_mutateNode, eggp_mutate_node_shuffle_host);
      freeMorphism(holder->morphism);
      free(holder);
      applyeggp_mutate_node_shuffle_mutateNode(M_eggp_mutate_node_shuffle_mutateNode, false);
      eggp_mutate_node_shuffle_success = true;
   }
   else
   {
      printf("No output graph: rule eggp_mutate_node_shuffle_mutateNode not applicable.\n");
      eggp_mutate_node_shuffle_garbageCollect();
      return 0;
   }
   emptyPot(eggp_mutate_node_shuffle_pot);
   /* Loop Statement */
   while(eggp_mutate_node_shuffle_success)
   {
      /* Rule Set Call */
      do
      {
         if(matcheggp_mutate_node_shuffle_markOutputsBlue(M_eggp_mutate_node_shuffle_markOutputsBlue))
         {
            applyeggp_mutate_node_shuffle_markOutputsBlue(M_eggp_mutate_node_shuffle_markOutputsBlue, false);
            eggp_mutate_node_shuffle_success = true;
            break;
         }
         if(matcheggp_mutate_node_shuffle_markOutputsRed(M_eggp_mutate_node_shuffle_markOutputsRed))
         {
            applyeggp_mutate_node_shuffle_markOutputsRed(M_eggp_mutate_node_shuffle_markOutputsRed, false);
            eggp_mutate_node_shuffle_success = true;
         }
         else
         {
            eggp_mutate_node_shuffle_success = false;
         }
      } while(false);
   }
   eggp_mutate_node_shuffle_success = true;
   /* Loop Statement */
   while(eggp_mutate_node_shuffle_success)
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
      if(matcheggp_mutate_node_shuffle_addEdgeToArity(M_eggp_mutate_node_shuffle_addEdgeToArity)){
         valid[0] = true;
         totalWeight = totalWeight + weight[0];
         someValid = true;
      }
      initialiseMorphism(M_eggp_mutate_node_shuffle_addEdgeToArity, eggp_mutate_node_shuffle_host);
      valid[1] = false;
      weight[1] = 1.000000;
      if(matcheggp_mutate_node_shuffle_deleteEdgeToArity(M_eggp_mutate_node_shuffle_deleteEdgeToArity)){
         valid[1] = true;
         totalWeight = totalWeight + weight[1];
         someValid = true;
      }
      initialiseMorphism(M_eggp_mutate_node_shuffle_deleteEdgeToArity, eggp_mutate_node_shuffle_host);
      if (someValid){
         double r = ((double)rand() / (double)RAND_MAX);
         r = r * totalWeight;
         double sum = 0.0;
         if(valid[0]){
            sum = sum + weight[0];
            if(r <= sum){
               emptyPot(eggp_mutate_node_shuffle_pot);
               fillpoteggp_mutate_node_shuffle_addEdgeToArity(eggp_mutate_node_shuffle_pot, M_eggp_mutate_node_shuffle_addEdgeToArity);
               if(potSize(eggp_mutate_node_shuffle_pot) > 0){
                  MorphismHolder *holder = drawFromPot(eggp_mutate_node_shuffle_pot);
                  duplicateMorphism(holder->morphism, M_eggp_mutate_node_shuffle_addEdgeToArity, eggp_mutate_node_shuffle_host);
                  freeMorphism(holder->morphism);
                  free(holder);
                  applyeggp_mutate_node_shuffle_addEdgeToArity(M_eggp_mutate_node_shuffle_addEdgeToArity, false);
                  eggp_mutate_node_shuffle_success = true;
                  break;
               }
               emptyPot(eggp_mutate_node_shuffle_pot);
            }
         }
         if(valid[1]){
            sum = sum + weight[1];
            if(r <= sum && r > sum - weight[1]){
               emptyPot(eggp_mutate_node_shuffle_pot);
               fillpoteggp_mutate_node_shuffle_deleteEdgeToArity(eggp_mutate_node_shuffle_pot, M_eggp_mutate_node_shuffle_deleteEdgeToArity);
               if(potSize(eggp_mutate_node_shuffle_pot) > 0){
                  MorphismHolder *holder = drawFromPot(eggp_mutate_node_shuffle_pot);
                  duplicateMorphism(holder->morphism, M_eggp_mutate_node_shuffle_deleteEdgeToArity, eggp_mutate_node_shuffle_host);
                  freeMorphism(holder->morphism);
                  free(holder);
                  applyeggp_mutate_node_shuffle_deleteEdgeToArity(M_eggp_mutate_node_shuffle_deleteEdgeToArity, false);
                  eggp_mutate_node_shuffle_success = true;
                  break;
               }
               emptyPot(eggp_mutate_node_shuffle_pot);
            }
         }
      } else {
      eggp_mutate_node_shuffle_success = false;
      }
      } while(false);
   }
   eggp_mutate_node_shuffle_success = true;
   /* Loop Statement */
   while(eggp_mutate_node_shuffle_success)
   {
      /* Rule Call */
      if(matcheggp_mutate_node_shuffle_unmarkBlue(M_eggp_mutate_node_shuffle_unmarkBlue))
      {
         applyeggp_mutate_node_shuffle_unmarkBlue(M_eggp_mutate_node_shuffle_unmarkBlue, false);
         eggp_mutate_node_shuffle_success = true;
      }
      else
      {
         eggp_mutate_node_shuffle_success = false;
      }
   }
   eggp_mutate_node_shuffle_success = true;
   /* Rule Call */
   if(matcheggp_mutate_node_shuffle_resetArityCounter(M_eggp_mutate_node_shuffle_resetArityCounter))
   {
      applyeggp_mutate_node_shuffle_resetArityCounter(M_eggp_mutate_node_shuffle_resetArityCounter, false);
      eggp_mutate_node_shuffle_success = true;
   }
   else
   {
      printf("No output graph: rule eggp_mutate_node_shuffle_resetArityCounter not applicable.\n");
      eggp_mutate_node_shuffle_garbageCollect();
      return 0;
   }
   /* Loop Statement */
   while(eggp_mutate_node_shuffle_success)
   {
      /* Rule Call */
      if(matcheggp_mutate_node_shuffle_bucketEdge(M_eggp_mutate_node_shuffle_bucketEdge))
      {
         applyeggp_mutate_node_shuffle_bucketEdge(M_eggp_mutate_node_shuffle_bucketEdge, false);
         eggp_mutate_node_shuffle_success = true;
      }
      else
      {
         eggp_mutate_node_shuffle_success = false;
      }
   }
   eggp_mutate_node_shuffle_success = true;
   /* Loop Statement */
   while(eggp_mutate_node_shuffle_success)
   {
      /* Rule Call */
      emptyPot(eggp_mutate_node_shuffle_pot);
      fillpoteggp_mutate_node_shuffle_readdEdge(eggp_mutate_node_shuffle_pot, M_eggp_mutate_node_shuffle_readdEdge);
      if(potSize(eggp_mutate_node_shuffle_pot) > 0){
         MorphismHolder *holder = drawFromPot(eggp_mutate_node_shuffle_pot);
         duplicateMorphism(holder->morphism, M_eggp_mutate_node_shuffle_readdEdge, eggp_mutate_node_shuffle_host);
         freeMorphism(holder->morphism);
         free(holder);
         applyeggp_mutate_node_shuffle_readdEdge(M_eggp_mutate_node_shuffle_readdEdge, false);
         eggp_mutate_node_shuffle_success = true;
      }
      else
      {
         eggp_mutate_node_shuffle_success = false;
      }
      emptyPot(eggp_mutate_node_shuffle_pot);
   }
   eggp_mutate_node_shuffle_success = true;
   /* Rule Call */
   if(matcheggp_mutate_node_shuffle_deleteArityC(M_eggp_mutate_node_shuffle_deleteArityC))
   {
      applyeggp_mutate_node_shuffle_deleteArityC(M_eggp_mutate_node_shuffle_deleteArityC, false);
      eggp_mutate_node_shuffle_success = true;
   }
   else
   {
      printf("No output graph: rule eggp_mutate_node_shuffle_deleteArityC not applicable.\n");
      eggp_mutate_node_shuffle_garbageCollect();
      return 0;
   }
   /* Loop Statement */
   while(eggp_mutate_node_shuffle_success)
   {
      /* Rule Set Call */
      do
      {
         if(matcheggp_mutate_node_shuffle_unmarkBlue(M_eggp_mutate_node_shuffle_unmarkBlue))
         {
            applyeggp_mutate_node_shuffle_unmarkBlue(M_eggp_mutate_node_shuffle_unmarkBlue, false);
            eggp_mutate_node_shuffle_success = true;
            break;
         }
         if(matcheggp_mutate_node_shuffle_unmarkRed(M_eggp_mutate_node_shuffle_unmarkRed))
         {
            applyeggp_mutate_node_shuffle_unmarkRed(M_eggp_mutate_node_shuffle_unmarkRed, false);
            eggp_mutate_node_shuffle_success = true;
         }
         else
         {
            eggp_mutate_node_shuffle_success = false;
         }
      } while(false);
   }
   eggp_mutate_node_shuffle_success = true;
   eggp_mutate_node_shuffle_garbageCollect();
   return 0;
}


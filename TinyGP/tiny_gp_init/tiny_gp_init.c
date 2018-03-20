#include <time.h>
#include "common.h"
#include "debug.h"
#include "graph.h"
#include "graphStacks.h"
#include "parser.h"
#include "morphism.h"

#include "tiny_gp_init_init_depth.h"
Morphism *M_tiny_gp_init_init_depth = NULL;
#include "tiny_gp_init_growOut.h"
Morphism *M_tiny_gp_init_growOut = NULL;
#include "tiny_gp_init_growFunc.h"
Morphism *M_tiny_gp_init_growFunc = NULL;
#include "tiny_gp_init_growInput.h"
Morphism *M_tiny_gp_init_growInput = NULL;
#include "tiny_gp_init_closeFunc.h"
Morphism *M_tiny_gp_init_closeFunc = NULL;
#include "tiny_gp_init_removeDepth.h"
Morphism *M_tiny_gp_init_removeDepth = NULL;
#include "tiny_gp_init_unmark.h"
Morphism *M_tiny_gp_init_unmark = NULL;

static void tiny_gp_init_freeMorphisms(void)
{
   freeMorphism(M_tiny_gp_init_init_depth);
   freeMorphism(M_tiny_gp_init_growOut);
   freeMorphism(M_tiny_gp_init_growFunc);
   freeMorphism(M_tiny_gp_init_growInput);
   freeMorphism(M_tiny_gp_init_closeFunc);
   freeMorphism(M_tiny_gp_init_removeDepth);
   freeMorphism(M_tiny_gp_init_unmark);
}

Graph* tiny_gp_init_host = NULL;
int* tiny_gp_init_node_map = NULL;
MorphismPot* tiny_gp_init_pot = NULL;

static void tiny_gp_init_garbageCollect(void)
{
   tiny_gp_init_freeMorphisms();
   freePot(tiny_gp_init_pot);
}

bool tiny_gp_init_success = true;

int tiny_gp_init_execute(Graph* host_graph)
{
   tiny_gp_init_host = host_graph;
   tiny_gp_init_success = true;
   tiny_gp_init_pot = makeMorphismPot();
   emptyPot(tiny_gp_init_pot);
   M_tiny_gp_init_init_depth = makeMorphism(1, 0, 1);
   M_tiny_gp_init_growOut = makeMorphism(2, 0, 4);
   M_tiny_gp_init_growFunc = makeMorphism(3, 1, 6);
   M_tiny_gp_init_growInput = makeMorphism(3, 1, 5);
   M_tiny_gp_init_closeFunc = makeMorphism(1, 1, 2);
   M_tiny_gp_init_removeDepth = makeMorphism(1, 0, 3);
   M_tiny_gp_init_unmark = makeMorphism(1, 0, 1);

   /* Rule Call */
   if(matchtiny_gp_init_init_depth(M_tiny_gp_init_init_depth))
   {
      applytiny_gp_init_init_depth(M_tiny_gp_init_init_depth, false);
      tiny_gp_init_success = true;
   }
   else
   {
      printf("No output graph: rule tiny_gp_init_init_depth not applicable.\n");
      tiny_gp_init_garbageCollect();
      return 0;
   }
   /* Rule Call */
   emptyPot(tiny_gp_init_pot);
   fillpottiny_gp_init_growOut(tiny_gp_init_pot, M_tiny_gp_init_growOut);
   if(potSize(tiny_gp_init_pot) > 0){
      MorphismHolder *holder = drawFromPot(tiny_gp_init_pot);
      duplicateMorphism(holder->morphism, M_tiny_gp_init_growOut, tiny_gp_init_host);
      freeMorphism(holder->morphism);
      free(holder);
      applytiny_gp_init_growOut(M_tiny_gp_init_growOut, false);
      tiny_gp_init_success = true;
   }
   else
   {
      printf("No output graph: rule tiny_gp_init_growOut not applicable.\n");
      tiny_gp_init_garbageCollect();
      return 0;
   }
   emptyPot(tiny_gp_init_pot);
   /* Loop Statement */
   int restore_point0 = graph_change_stack == NULL ? 0 : topOfGraphChangeStack();
   while(tiny_gp_init_success)
   {
      /* Rule Set Call */
      do
      {
      bool valid[2];
      double weight[2];
      double totalWeight = 0.0;
      bool someValid = false;
      valid[0] = false;
      weight[0] = 1.0;
      valid[1] = false;
      weight[1] = 1.0;
      valid[0] = false;
      weight[0] = 1.000000;
      if(matchtiny_gp_init_growFunc(M_tiny_gp_init_growFunc)){
         valid[0] = true;
         totalWeight = totalWeight + weight[0];
         someValid = true;
      }
      initialiseMorphism(M_tiny_gp_init_growFunc, tiny_gp_init_host);
      valid[1] = false;
      weight[1] = 1.000000;
      if(matchtiny_gp_init_growInput(M_tiny_gp_init_growInput)){
         valid[1] = true;
         totalWeight = totalWeight + weight[1];
         someValid = true;
      }
      initialiseMorphism(M_tiny_gp_init_growInput, tiny_gp_init_host);
      if (someValid){
         double r = ((double)rand() / (double)RAND_MAX);
         r = r * totalWeight;
         double sum = 0.0;
         if(valid[0]){
            sum = sum + weight[0];
            if(r <= sum){
               emptyPot(tiny_gp_init_pot);
               fillpottiny_gp_init_growFunc(tiny_gp_init_pot, M_tiny_gp_init_growFunc);
               if(potSize(tiny_gp_init_pot) > 0){
                  MorphismHolder *holder = drawFromPot(tiny_gp_init_pot);
                  duplicateMorphism(holder->morphism, M_tiny_gp_init_growFunc, tiny_gp_init_host);
                  freeMorphism(holder->morphism);
                  free(holder);
                  applytiny_gp_init_growFunc(M_tiny_gp_init_growFunc, true);
                  tiny_gp_init_success = true;
                  break;
               }
               emptyPot(tiny_gp_init_pot);
            }
         }
         if(valid[1]){
            sum = sum + weight[1];
            if(r <= sum && r > sum - weight[1]){
               emptyPot(tiny_gp_init_pot);
               fillpottiny_gp_init_growInput(tiny_gp_init_pot, M_tiny_gp_init_growInput);
               if(potSize(tiny_gp_init_pot) > 0){
                  MorphismHolder *holder = drawFromPot(tiny_gp_init_pot);
                  duplicateMorphism(holder->morphism, M_tiny_gp_init_growInput, tiny_gp_init_host);
                  freeMorphism(holder->morphism);
                  free(holder);
                  applytiny_gp_init_growInput(M_tiny_gp_init_growInput, true);
                  tiny_gp_init_success = true;
                  break;
               }
               emptyPot(tiny_gp_init_pot);
            }
         }
      } else {
      tiny_gp_init_success = false;
      undoChanges(tiny_gp_init_host, restore_point0);
      }
      } while(false);
      if(!tiny_gp_init_success) break;

      /* Loop Statement */
      while(tiny_gp_init_success)
      {
         /* Rule Call */
         if(matchtiny_gp_init_closeFunc(M_tiny_gp_init_closeFunc))
         {
            applytiny_gp_init_closeFunc(M_tiny_gp_init_closeFunc, true);
            tiny_gp_init_success = true;
         }
         else
         {
            tiny_gp_init_success = false;
         }
      }
      tiny_gp_init_success = true;
      /* Graph changes from loop body may not have been used.
         Discard them so that future graph roll backs are uncorrupted. */
      if(tiny_gp_init_success) discardChanges(restore_point0);
   }
   tiny_gp_init_success = true;
   /* Loop Statement */
   while(tiny_gp_init_success)
   {
      /* Rule Call */
      if(matchtiny_gp_init_removeDepth(M_tiny_gp_init_removeDepth))
      {
         applytiny_gp_init_removeDepth(M_tiny_gp_init_removeDepth, false);
         tiny_gp_init_success = true;
      }
      else
      {
         tiny_gp_init_success = false;
      }
   }
   tiny_gp_init_success = true;
   /* Loop Statement */
   while(tiny_gp_init_success)
   {
      /* Rule Call */
      if(matchtiny_gp_init_unmark(M_tiny_gp_init_unmark))
      {
         applytiny_gp_init_unmark(M_tiny_gp_init_unmark, false);
         tiny_gp_init_success = true;
      }
      else
      {
         tiny_gp_init_success = false;
      }
   }
   tiny_gp_init_success = true;
   tiny_gp_init_garbageCollect();
   return 0;
}


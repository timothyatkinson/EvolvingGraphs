#include <time.h>
#include "common.h"
#include "debug.h"
#include "graph.h"
#include "graphStacks.h"
#include "parser.h"
#include "morphism.h"

#include "tiny_gp_crossover_crossover_point.h"
Morphism *M_tiny_gp_crossover_crossover_point = NULL;
#include "tiny_gp_crossover_markRedFunc.h"
Morphism *M_tiny_gp_crossover_markRedFunc = NULL;
#include "tiny_gp_crossover_markBlueFunc.h"
Morphism *M_tiny_gp_crossover_markBlueFunc = NULL;
#include "tiny_gp_crossover_markRedEdge.h"
Morphism *M_tiny_gp_crossover_markRedEdge = NULL;
#include "tiny_gp_crossover_markBlueEdge.h"
Morphism *M_tiny_gp_crossover_markBlueEdge = NULL;
#include "tiny_gp_crossover_moveInputRed.h"
Morphism *M_tiny_gp_crossover_moveInputRed = NULL;
#include "tiny_gp_crossover_moveInputBlue.h"
Morphism *M_tiny_gp_crossover_moveInputBlue = NULL;

static void tiny_gp_crossover_freeMorphisms(void)
{
   freeMorphism(M_tiny_gp_crossover_crossover_point);
   freeMorphism(M_tiny_gp_crossover_markRedFunc);
   freeMorphism(M_tiny_gp_crossover_markBlueFunc);
   freeMorphism(M_tiny_gp_crossover_markRedEdge);
   freeMorphism(M_tiny_gp_crossover_markBlueEdge);
   freeMorphism(M_tiny_gp_crossover_moveInputRed);
   freeMorphism(M_tiny_gp_crossover_moveInputBlue);
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
   M_tiny_gp_crossover_markRedFunc = makeMorphism(2, 1, 4);
   M_tiny_gp_crossover_markBlueFunc = makeMorphism(2, 1, 4);
   M_tiny_gp_crossover_markRedEdge = makeMorphism(2, 1, 3);
   M_tiny_gp_crossover_markBlueEdge = makeMorphism(2, 1, 3);
   M_tiny_gp_crossover_moveInputRed = makeMorphism(3, 1, 5);
   M_tiny_gp_crossover_moveInputBlue = makeMorphism(3, 1, 5);

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
   /* Loop Statement */
   while(tiny_gp_crossover_success)
   {
      /* Rule Set Call */
      do
      {
         if(matchtiny_gp_crossover_markRedFunc(M_tiny_gp_crossover_markRedFunc))
         {
            applytiny_gp_crossover_markRedFunc(M_tiny_gp_crossover_markRedFunc, false);
            tiny_gp_crossover_success = true;
            break;
         }
         if(matchtiny_gp_crossover_markBlueFunc(M_tiny_gp_crossover_markBlueFunc))
         {
            applytiny_gp_crossover_markBlueFunc(M_tiny_gp_crossover_markBlueFunc, false);
            tiny_gp_crossover_success = true;
            break;
         }
         if(matchtiny_gp_crossover_markRedEdge(M_tiny_gp_crossover_markRedEdge))
         {
            applytiny_gp_crossover_markRedEdge(M_tiny_gp_crossover_markRedEdge, false);
            tiny_gp_crossover_success = true;
            break;
         }
         if(matchtiny_gp_crossover_markBlueEdge(M_tiny_gp_crossover_markBlueEdge))
         {
            applytiny_gp_crossover_markBlueEdge(M_tiny_gp_crossover_markBlueEdge, false);
            tiny_gp_crossover_success = true;
            break;
         }
         if(matchtiny_gp_crossover_moveInputRed(M_tiny_gp_crossover_moveInputRed))
         {
            applytiny_gp_crossover_moveInputRed(M_tiny_gp_crossover_moveInputRed, false);
            tiny_gp_crossover_success = true;
            break;
         }
         if(matchtiny_gp_crossover_moveInputBlue(M_tiny_gp_crossover_moveInputBlue))
         {
            applytiny_gp_crossover_moveInputBlue(M_tiny_gp_crossover_moveInputBlue, false);
            tiny_gp_crossover_success = true;
         }
         else
         {
            tiny_gp_crossover_success = false;
         }
      } while(false);
   }
   tiny_gp_crossover_success = true;
   tiny_gp_crossover_garbageCollect();
   return 0;
}


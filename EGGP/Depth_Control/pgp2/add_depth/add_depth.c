#include <time.h>
#include "common.h"
#include "debug.h"
#include "graph.h"
#include "graphStacks.h"
#include "parser.h"
#include "morphism.h"

#include "add_depth_initInput.h"
Morphism *M_add_depth_initInput = NULL;
#include "add_depth_initOutput.h"
Morphism *M_add_depth_initOutput = NULL;
#include "add_depth_initNode.h"
Morphism *M_add_depth_initNode = NULL;
#include "add_depth_incIn.h"
Morphism *M_add_depth_incIn = NULL;
#include "add_depth_incOut.h"
Morphism *M_add_depth_incOut = NULL;
#include "add_depth_unmark.h"
Morphism *M_add_depth_unmark = NULL;

static void add_depth_freeMorphisms(void)
{
   freeMorphism(M_add_depth_initInput);
   freeMorphism(M_add_depth_initOutput);
   freeMorphism(M_add_depth_initNode);
   freeMorphism(M_add_depth_incIn);
   freeMorphism(M_add_depth_incOut);
   freeMorphism(M_add_depth_unmark);
}

Graph* add_depth_host = NULL;
int* add_depth_node_map = NULL;
MorphismPot* add_depth_pot = NULL;

static void add_depth_garbageCollect(void)
{
   add_depth_freeMorphisms();
   freePot(add_depth_pot);
}

bool add_depth_success = true;

int add_depth_execute(Graph* host_graph)
{
   add_depth_host = host_graph;
   add_depth_success = true;
   add_depth_pot = makeMorphismPot();
   emptyPot(add_depth_pot);
   M_add_depth_initInput = makeMorphism(1, 0, 1);
   M_add_depth_initOutput = makeMorphism(1, 0, 1);
   M_add_depth_initNode = makeMorphism(1, 0, 2);
   M_add_depth_incIn = makeMorphism(2, 1, 9);
   M_add_depth_incOut = makeMorphism(2, 1, 9);
   M_add_depth_unmark = makeMorphism(1, 0, 1);

   /* Loop Statement */
   while(add_depth_success)
   {
      /* Rule Set Call */
      do
      {
         if(matchadd_depth_initInput(M_add_depth_initInput))
         {
            applyadd_depth_initInput(M_add_depth_initInput, false);
            add_depth_success = true;
            break;
         }
         if(matchadd_depth_initOutput(M_add_depth_initOutput))
         {
            applyadd_depth_initOutput(M_add_depth_initOutput, false);
            add_depth_success = true;
         }
         else
         {
            add_depth_success = false;
         }
      } while(false);
   }
   add_depth_success = true;
   /* Loop Statement */
   while(add_depth_success)
   {
      /* Rule Call */
      if(matchadd_depth_initNode(M_add_depth_initNode))
      {
         applyadd_depth_initNode(M_add_depth_initNode, false);
         add_depth_success = true;
      }
      else
      {
         add_depth_success = false;
      }
   }
   add_depth_success = true;
   /* Loop Statement */
   while(add_depth_success)
   {
      /* Rule Call */
      if(matchadd_depth_incIn(M_add_depth_incIn))
      {
         applyadd_depth_incIn(M_add_depth_incIn, false);
         add_depth_success = true;
      }
      else
      {
         add_depth_success = false;
      }
   }
   add_depth_success = true;
   /* Loop Statement */
   while(add_depth_success)
   {
      /* Rule Call */
      if(matchadd_depth_incOut(M_add_depth_incOut))
      {
         applyadd_depth_incOut(M_add_depth_incOut, false);
         add_depth_success = true;
      }
      else
      {
         add_depth_success = false;
      }
   }
   add_depth_success = true;
   /* Loop Statement */
   while(add_depth_success)
   {
      /* Rule Call */
      if(matchadd_depth_unmark(M_add_depth_unmark))
      {
         applyadd_depth_unmark(M_add_depth_unmark, false);
         add_depth_success = true;
      }
      else
      {
         add_depth_success = false;
      }
   }
   add_depth_success = true;
   add_depth_garbageCollect();
   return 0;
}


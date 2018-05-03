#include <time.h>
#include "common.h"
#include "debug.h"
#include "graph.h"
#include "graphStacks.h"
#include "parser.h"
#include "morphism.h"

#include "remove_depth_removeDepth.h"
Morphism *M_remove_depth_removeDepth = NULL;
#include "remove_depth_unmark.h"
Morphism *M_remove_depth_unmark = NULL;

static void remove_depth_freeMorphisms(void)
{
   freeMorphism(M_remove_depth_removeDepth);
   freeMorphism(M_remove_depth_unmark);
}

Graph* remove_depth_host = NULL;
int* remove_depth_node_map = NULL;
MorphismPot* remove_depth_pot = NULL;

static void remove_depth_garbageCollect(void)
{
   remove_depth_freeMorphisms();
   freePot(remove_depth_pot);
}

bool remove_depth_success = true;

int remove_depth_execute(Graph* host_graph)
{
   remove_depth_host = host_graph;
   remove_depth_success = true;
   remove_depth_pot = makeMorphismPot();
   emptyPot(remove_depth_pot);
   M_remove_depth_removeDepth = makeMorphism(1, 0, 4);
   M_remove_depth_unmark = makeMorphism(1, 0, 1);

   /* Loop Statement */
   while(remove_depth_success)
   {
      /* Rule Call */
      if(matchremove_depth_removeDepth(M_remove_depth_removeDepth))
      {
         applyremove_depth_removeDepth(M_remove_depth_removeDepth, false);
         remove_depth_success = true;
      }
      else
      {
         remove_depth_success = false;
      }
   }
   remove_depth_success = true;
   /* Loop Statement */
   while(remove_depth_success)
   {
      /* Rule Call */
      if(matchremove_depth_unmark(M_remove_depth_unmark))
      {
         applyremove_depth_unmark(M_remove_depth_unmark, false);
         remove_depth_success = true;
      }
      else
      {
         remove_depth_success = false;
      }
   }
   remove_depth_success = true;
   remove_depth_garbageCollect();
   return 0;
}


#include <time.h>
#include "common.h"
#include "debug.h"
#include "graph.h"
#include "graphStacks.h"
#include "parser.h"
#include "morphism.h"

#include "cgp_init_init_node_counter.h"
Morphism *M_cgp_init_init_node_counter = NULL;
#include "cgp_init_check_node_counter.h"
Morphism *M_cgp_init_check_node_counter = NULL;
#include "cgp_init_add_node.h"
Morphism *M_cgp_init_add_node = NULL;
#include "cgp_init_add_edge_to_arity.h"
Morphism *M_cgp_init_add_edge_to_arity = NULL;
#include "cgp_init_unmark_node.h"
Morphism *M_cgp_init_unmark_node = NULL;
#include "cgp_init_connect_output.h"
Morphism *M_cgp_init_connect_output = NULL;

static void cgp_init_freeMorphisms(void)
{
   freeMorphism(M_cgp_init_init_node_counter);
   freeMorphism(M_cgp_init_check_node_counter);
   freeMorphism(M_cgp_init_add_node);
   freeMorphism(M_cgp_init_add_edge_to_arity);
   freeMorphism(M_cgp_init_unmark_node);
   freeMorphism(M_cgp_init_connect_output);
}

Graph* cgp_init_host = NULL;
int* cgp_init_node_map = NULL;
MorphismPot* cgp_init_pot = NULL;

static void cgp_init_garbageCollect(void)
{
   cgp_init_freeMorphisms();
   freePot(cgp_init_pot);
}

bool cgp_init_success = true;

int cgp_init_execute(Graph* host_graph)
{
   cgp_init_host = host_graph;
   cgp_init_success = true;
   cgp_init_pot = makeMorphismPot();
   emptyPot(cgp_init_pot);
   M_cgp_init_init_node_counter = makeMorphism(1, 0, 1);
   M_cgp_init_check_node_counter = makeMorphism(2, 0, 2);
   M_cgp_init_add_node = makeMorphism(3, 0, 4);
   M_cgp_init_add_edge_to_arity = makeMorphism(3, 0, 8);
   M_cgp_init_unmark_node = makeMorphism(1, 0, 1);
   M_cgp_init_connect_output = makeMorphism(2, 0, 3);

   /* Rule Call */
   if(matchcgp_init_init_node_counter(M_cgp_init_init_node_counter))
   {
      applycgp_init_init_node_counter(M_cgp_init_init_node_counter, false);
      cgp_init_success = true;
   }
   else
   {
      printf("No output graph: rule cgp_init_init_node_counter not applicable.\n");
      cgp_init_garbageCollect();
      return 0;
   }
   /* Loop Statement */
   int restore_point0 = graph_change_stack == NULL ? 0 : topOfGraphChangeStack();
   while(cgp_init_success)
   {
      /* Rule Call */
      if(matchcgp_init_check_node_counter(M_cgp_init_check_node_counter))
      {
         cgp_init_success = true;
      }
      else
      {
         cgp_init_success = false;
         undoChanges(cgp_init_host, restore_point0);
      }
      if(!cgp_init_success) break;

      /* Rule Call */
      emptyPot(cgp_init_pot);
      fillpotcgp_init_add_node(cgp_init_pot, M_cgp_init_add_node);
      if(potSize(cgp_init_pot) > 0){
         MorphismHolder *holder = drawFromPot(cgp_init_pot);
         duplicateMorphism(holder->morphism, M_cgp_init_add_node, cgp_init_host);
         freeMorphism(holder->morphism);
         free(holder);
         applycgp_init_add_node(M_cgp_init_add_node, true);
         cgp_init_success = true;
      }
      else
      {
         cgp_init_success = false;
         undoChanges(cgp_init_host, restore_point0);
      }
      emptyPot(cgp_init_pot);
      if(!cgp_init_success) break;

      /* Loop Statement */
      while(cgp_init_success)
      {
         /* Rule Call */
         emptyPot(cgp_init_pot);
         fillpotcgp_init_add_edge_to_arity(cgp_init_pot, M_cgp_init_add_edge_to_arity);
         if(potSize(cgp_init_pot) > 0){
            MorphismHolder *holder = drawFromPot(cgp_init_pot);
            duplicateMorphism(holder->morphism, M_cgp_init_add_edge_to_arity, cgp_init_host);
            freeMorphism(holder->morphism);
            free(holder);
            applycgp_init_add_edge_to_arity(M_cgp_init_add_edge_to_arity, true);
            cgp_init_success = true;
         }
         else
         {
            cgp_init_success = false;
         }
         emptyPot(cgp_init_pot);
      }
      cgp_init_success = true;
      if(!cgp_init_success) break;

      /* Rule Call */
      if(matchcgp_init_unmark_node(M_cgp_init_unmark_node))
      {
         applycgp_init_unmark_node(M_cgp_init_unmark_node, true);
         cgp_init_success = true;
      }
      else
      {
         cgp_init_success = false;
         undoChanges(cgp_init_host, restore_point0);
      }
      /* Graph changes from loop body may not have been used.
         Discard them so that future graph roll backs are uncorrupted. */
      if(cgp_init_success) discardChanges(restore_point0);
   }
   cgp_init_success = true;
   /* Loop Statement */
   while(cgp_init_success)
   {
      /* Rule Call */
      emptyPot(cgp_init_pot);
      fillpotcgp_init_connect_output(cgp_init_pot, M_cgp_init_connect_output);
      if(potSize(cgp_init_pot) > 0){
         MorphismHolder *holder = drawFromPot(cgp_init_pot);
         duplicateMorphism(holder->morphism, M_cgp_init_connect_output, cgp_init_host);
         freeMorphism(holder->morphism);
         free(holder);
         applycgp_init_connect_output(M_cgp_init_connect_output, false);
         cgp_init_success = true;
      }
      else
      {
         cgp_init_success = false;
      }
      emptyPot(cgp_init_pot);
   }
   cgp_init_success = true;
   cgp_init_garbageCollect();
   return 0;
}


#include "tiny_gp_init_closeFunc.h"

#include "tiny_gp_init.h"

bool tiny_gp_init_b4 = true;

static bool evaluateCondition(void)
{
   return (tiny_gp_init_b4);
}

static void evaluatePredicatetiny_gp_init_4(Morphism *morphism)
{
   Assignment assignment_1 = getAssignment(morphism, 1);
   /* If the variable is not yet assigned, return. */
   if(assignment_1.type == 'n') return;
   int var_1 = getIntegerValue(morphism, 1);

   if(var_1 == 0) tiny_gp_init_b4 = true;
   else tiny_gp_init_b4 = false;
}

static bool match_n0(Morphism *morphism);
static bool match_e0(Morphism *morphism);

bool matchtiny_gp_init_closeFunc(Morphism *morphism)
{
   if(1 > tiny_gp_init_host->number_of_nodes || 1 > tiny_gp_init_host->number_of_edges) return false;
   if(match_n0(morphism)) return true;
   else
   {
      initialiseMorphism(morphism, tiny_gp_init_host);
      return false;
   }
}

static bool match_n0(Morphism *morphism)
{
   RootNodes *nodes;
   for(nodes = getRootNodeList(tiny_gp_init_host); nodes != NULL; nodes = nodes->next)
   {
      Node *host_node = getNode(tiny_gp_init_host, nodes->index);
      if(host_node == NULL) continue;
      if(host_node->matched) continue;
      if(host_node->label.mark != 0) continue;
      if(host_node->indegree < 1 || host_node->outdegree < 1 ||
         ((host_node->outdegree + host_node->indegree - 1 - 1 - 0) < 0)) continue;

      HostLabel label = host_node->label;
      bool match = false;
      /* Label Matching */
      int new_assignments = 0;
      /* Match list variable 0 against the whole host list. */
      int result = -1;
      if(label.length == 1)
      {
         if(label.list->first->atom.type == 'i')
            result = addIntegerAssignment(morphism, 0, label.list->first->atom.num);
         else result = addStringAssignment(morphism, 0, label.list->first->atom.str);
      }
      else result = addListAssignment(morphism, 0, label.list);
      if(result >= 0)
      {
         new_assignments += result;
         match = true;
      }
      if(match)
      {
         addNodeMap(morphism, 0, host_node->index, new_assignments);
         host_node->matched = true;
         if(match_e0(morphism)) return true;
         else
         {
         removeNodeMap(morphism, 0);
         host_node->matched = false;
         }
      }
      else removeAssignments(morphism, new_assignments);
   }
   return false;
}

static bool match_e0(Morphism *morphism)
{
   /* Matching a loop. */
   int node_index = lookupNode(morphism, 0);
   if(node_index < 0) return false;
   Node *host_node = getNode(tiny_gp_init_host, node_index);

   int counter;
   for(counter = 0; counter < host_node->out_edges.size + 2; counter++)
   {
      Edge *host_edge = getNthOutEdge(tiny_gp_init_host, host_node, counter);
      if(host_edge == NULL) continue;
      if(host_edge->matched) continue;
      if(host_edge->source != host_edge->target) continue;
      if(host_edge->label.mark != 0) continue;

      HostLabel label = host_edge->label;
      bool match = false;
      /* Label Matching */
      int new_assignments = 0;
      do
      {
         /* The rule list does not contain a list variable, so there is no
          * match if the host list has a different length. */
         if(label.length != 1) break;
         HostListItem *item = label.list->first;
         /* Matching rule atom 1. */
         int result = -1;
         /* Matching integer variable 1. */
         if(item->atom.type != 'i') break;
         result = addIntegerAssignment(morphism, 1, item->atom.num);
         if(result >= 0)
         {
            new_assignments += result;
            /* Update global booleans for the variable's predicates. */
            evaluatePredicatetiny_gp_init_4(morphism);
            if(!evaluateCondition())
            {
               /* Reset the boolean variables in the predicates of this variable. */
               tiny_gp_init_b4 = true;
               break;
            }
         }
         else break;
         match = true;
      } while(false);

      if(match)
      {
         addEdgeMap(morphism, 0, host_edge->index, new_assignments);
         host_edge->matched = true;
      /* All items matched! */
            return true;
      }
      else removeAssignments(morphism, new_assignments);
   }
   return false;
}

void applytiny_gp_init_closeFunc(Morphism *morphism, bool record_changes)
{
   int host_edge_index = lookupEdge(morphism, 0);
   if(record_changes)
   {
      Edge *edge = getEdge(tiny_gp_init_host, host_edge_index);
      /* A hole is created if the edge is not at the right-most index of the array. */
      pushRemovedEdge(edge->label, edge->source, edge->target, edge->index,
                      edge->index < tiny_gp_init_host->edges.size - 1);
   }
   removeEdge(tiny_gp_init_host, host_edge_index);

   int host_node_index = lookupNode(morphism, 0);
   if(record_changes) pushChangedRootNode(host_node_index);
   changeRoot(tiny_gp_init_host, host_node_index);
   /* Reset the morphism. */
   initialiseMorphism(morphism, tiny_gp_init_host);
}

static bool fillpot_n0(MorphismPot *pot, Morphism *morphism);
static bool fillpot_e0(MorphismPot *pot, Morphism *morphism);

bool fillpottiny_gp_init_closeFunc(MorphismPot *pot, Morphism *morphism)
{
   if(1 > tiny_gp_init_host->number_of_nodes || 1 > tiny_gp_init_host->number_of_edges) return false;
   int oldPotsize = potSize(pot);
   morphism->weight = 0.000000;
   fillpot_n0(pot, morphism);
   if(potSize(pot) > oldPotsize){
      initialiseMorphism(morphism, tiny_gp_init_host);
      return true;
   }
   else
   {
      initialiseMorphism(morphism, tiny_gp_init_host);
      return false;
   }
}

static bool fillpot_n0(MorphismPot *pot, Morphism *morphism)
{
   RootNodes *nodes;
   for(nodes = getRootNodeList(tiny_gp_init_host); nodes != NULL; nodes = nodes->next)
   {
      Node *host_node = getNode(tiny_gp_init_host, nodes->index);
      if(host_node == NULL) continue;
      if(host_node->matched) continue;
      if(host_node->label.mark != 0) continue;
      if(host_node->indegree < 1 || host_node->outdegree < 1 ||
         ((host_node->outdegree + host_node->indegree - 1 - 1 - 0) < 0)) continue;

      HostLabel label = host_node->label;
      bool match = false;
      /* Label Matching */
      int new_assignments = 0;
      /* Match list variable 0 against the whole host list. */
      int result = -1;
      if(label.length == 1)
      {
         if(label.list->first->atom.type == 'i')
            result = addIntegerAssignment(morphism, 0, label.list->first->atom.num);
         else result = addStringAssignment(morphism, 0, label.list->first->atom.str);
      }
      else result = addListAssignment(morphism, 0, label.list);
      if(result >= 0)
      {
         new_assignments += result;
         match = true;
      }
      if(match)
      {
         addNodeMap(morphism, 0, host_node->index, new_assignments);
         host_node->matched = true;
         if(fillpot_e0(pot, morphism)) return true;
         else
         {
         removeNodeMap(morphism, 0);
         host_node->matched = false;
         }
      }
      else removeAssignments(morphism, new_assignments);
   }
   return false;
}

static bool fillpot_e0(MorphismPot *pot, Morphism *morphism)
{
   /* Matching a loop. */
   int node_index = lookupNode(morphism, 0);
   if(node_index < 0) return false;
   Node *host_node = getNode(tiny_gp_init_host, node_index);

   int counter;
   for(counter = 0; counter < host_node->out_edges.size + 2; counter++)
   {
      Edge *host_edge = getNthOutEdge(tiny_gp_init_host, host_node, counter);
      if(host_edge == NULL) continue;
      if(host_edge->matched) continue;
      if(host_edge->source != host_edge->target) continue;
      if(host_edge->label.mark != 0) continue;

      HostLabel label = host_edge->label;
      bool match = false;
      /* Label Matching */
      int new_assignments = 0;
      do
      {
         /* The rule list does not contain a list variable, so there is no
          * match if the host list has a different length. */
         if(label.length != 1) break;
         HostListItem *item = label.list->first;
         /* Matching rule atom 1. */
         int result = -1;
         /* Matching integer variable 1. */
         if(item->atom.type != 'i') break;
         result = addIntegerAssignment(morphism, 1, item->atom.num);
         if(result >= 0)
         {
            new_assignments += result;
            /* Update global booleans for the variable's predicates. */
            evaluatePredicatetiny_gp_init_4(morphism);
            if(!evaluateCondition())
            {
               /* Reset the boolean variables in the predicates of this variable. */
               tiny_gp_init_b4 = true;
               break;
            }
         }
         else break;
         match = true;
      } while(false);

      if(match)
      {
         addEdgeMap(morphism, 0, host_edge->index, new_assignments);
         host_edge->matched = true;
      /* All items matched! */
            putMorphism(pot, morphism, "tiny_gp_init_closeFunc", tiny_gp_init_host);
            removeEdgeMap(morphism, 0);
            host_edge->matched = false;
            return false;
      }
      else removeAssignments(morphism, new_assignments);
   }
   return false;
}


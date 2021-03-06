#include "n_node_propActive.h"

#include "n_node.h"

bool n_node_b1 = false;

static bool evaluateCondition(void)
{
   return (!n_node_b1);
}

static void evaluatePredicaten_node_1(Morphism *morphism)
{
   int n1 = lookupNode(morphism, 1);
   /* If the node is not yet matched by the morphism, return. */
   if(n1 == -1) return;

   int n2 = lookupNode(morphism, 2);
   /* If the node is not yet matched by the morphism, return. */
   if(n2 == -1) return;

   Node *source = getNode(n_node_host, n2);
   bool edge_found = false;
   int counter;
   for(counter = 0; counter < source->out_edges.size + 2; counter++)
   {
      Edge *edge = getNthOutEdge(n_node_host, source, counter);
      if(edge != NULL && edge->target == n1)
      {
         n_node_b1 = true;
         edge_found = true;
         break;
      }
   }
   if(!edge_found) n_node_b1 = false;
}

static bool match_n2(Morphism *morphism);
static bool match_n0(Morphism *morphism);
static bool match_e0(Morphism *morphism);
static bool match_n1(Morphism *morphism, Edge *host_edge);

bool matchn_node_propActive(Morphism *morphism)
{
   if(3 > n_node_host->number_of_nodes || 1 > n_node_host->number_of_edges) return false;
   if(match_n2(morphism)) return true;
   else
   {
      initialiseMorphism(morphism, n_node_host);
      return false;
   }
}

static bool match_n2(Morphism *morphism)
{
   RootNodes *nodes;
   for(nodes = getRootNodeList(n_node_host); nodes != NULL; nodes = nodes->next)
   {
      Node *host_node = getNode(n_node_host, nodes->index);
      if(host_node == NULL) continue;
      if(host_node->matched) continue;
      if(host_node->label.mark != 4) continue;
      if(host_node->indegree < 0 || host_node->outdegree < 0 ||
         ((host_node->outdegree + host_node->indegree - 0 - 0 - 0) < 0)) continue;

      HostLabel label = host_node->label;
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
         if(item->atom.type != 's') break;
         else if(strcmp(item->atom.str, "Active") != 0) break;
         match = true;
      } while(false);

      if(match)
      {
         addNodeMap(morphism, 2, host_node->index, new_assignments);
         host_node->matched = true;
         /* Update global booleans representing the node's predicates. */
         evaluatePredicaten_node_1(morphism);
         bool next_match_result = false;
         if(evaluateCondition()) next_match_result = match_n0(morphism);
         if(next_match_result) return true;
         else
         {
            /* Reset the boolean variables in the predicates of this node. */
            n_node_b1 = false;
            removeNodeMap(morphism, 2);
            host_node->matched = false;
         }
      }
      else removeAssignments(morphism, new_assignments);
   }
   return false;
}

static bool match_n0(Morphism *morphism)
{
   int host_index;
   for(host_index = 0; host_index < n_node_host->nodes.size; host_index++)
   {
      Node *host_node = getNode(n_node_host, host_index);
      if(host_node == NULL || host_node->index == -1) continue;
      if(host_node->matched) continue;
      if(host_node->label.mark != 0) continue;
      if(host_node->indegree < 0 || host_node->outdegree < 1 ||
         ((host_node->outdegree + host_node->indegree - 1 - 0 - 0) < 0)) continue;

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
   /* Start node is the already-matched node from which the candidate
      edges are drawn. End node may or may not have been matched already. */
   int start_index = lookupNode(morphism, 0);
   int end_index = lookupNode(morphism, 1);
   if(start_index < 0) return false;
   Node *host_node = getNode(n_node_host, start_index);

   int counter;
   for(counter = 0; counter < host_node->out_edges.size + 2; counter++)
   {
      Edge *host_edge = getNthOutEdge(n_node_host, host_node, counter);
      if(host_edge == NULL) continue;
      if(host_edge->matched) continue;
      if(host_edge->source == host_edge->target) continue;
      if(host_edge->label.mark != 0) continue;

      /* If the end node has been matched, check that the target of the
       * host edge is the image of the end node. */
      if(end_index >= 0)
      {
         if(host_edge->target != end_index) continue;
      }
      /* Otherwise, the target of the host edge should be unmatched. */
      else
      {
         Node *end_node = getNode(n_node_host, host_edge->target);
         if(end_node->matched) continue;
      }

      HostLabel label = host_edge->label;
      bool match = false;
      /* Label Matching */
      int new_assignments = 0;
      /* Match list variable 2 against the whole host list. */
      int result = -1;
      if(label.length == 1)
      {
         if(label.list->first->atom.type == 'i')
            result = addIntegerAssignment(morphism, 2, label.list->first->atom.num);
         else result = addStringAssignment(morphism, 2, label.list->first->atom.str);
      }
      else result = addListAssignment(morphism, 2, label.list);
      if(result >= 0)
      {
         new_assignments += result;
         match = true;
      }
      if(match)
      {
         addEdgeMap(morphism, 0, host_edge->index, new_assignments);
         host_edge->matched = true;
         if(match_n1(morphism, host_edge)) return true;
         else
         {
            removeEdgeMap(morphism, 0);
            host_edge->matched = false;
         }
      }
      else removeAssignments(morphism, new_assignments);
   }
   return false;
}

static bool match_n1(Morphism *morphism, Edge *host_edge)
{
   Node *host_node = getTarget(n_node_host, host_edge);

   if(host_node->matched) return false;
   if(host_node->label.mark != 0) return false;
      if(host_node->indegree < 1 || host_node->outdegree < 0 ||
         ((host_node->outdegree + host_node->indegree - 0 - 1 - 0) < 0)) return false;;

   HostLabel label = host_node->label;
   bool match = false;
   /* Label Matching */
   int new_assignments = 0;
   /* Match list variable 1 against the whole host list. */
   int result = -1;
   if(label.length == 1)
   {
      if(label.list->first->atom.type == 'i')
         result = addIntegerAssignment(morphism, 1, label.list->first->atom.num);
      else result = addStringAssignment(morphism, 1, label.list->first->atom.str);
   }
   else result = addListAssignment(morphism, 1, label.list);
   if(result >= 0)
   {
      new_assignments += result;
      match = true;
   }
   if(match)
   {
      addNodeMap(morphism, 1, host_node->index, new_assignments);
      host_node->matched = true;
      /* Update global booleans representing the node's predicates. */
      evaluatePredicaten_node_1(morphism);
      if(evaluateCondition())
      {
         /* All items matched! */
         return true;
      }
      else
      {
         /* Reset the boolean variables in the predicates of this node. */
         n_node_b1 = false;
         removeNodeMap(morphism, 1);
         host_node->matched = false;
      }
   }
   else removeAssignments(morphism, new_assignments);
   return false;
}

void applyn_node_propActive(Morphism *morphism, bool record_changes)
{
   int host_edge_index;
   int source, target;
   int edge_array_size1 = n_node_host->edges.size;
   source = lookupNode(morphism, 2);
   target = lookupNode(morphism, 1);
   HostLabel label;
   label = makeEmptyLabel(5);

   host_edge_index = addEdge(n_node_host, label, source, target);
   /* If the edge array size has not increased after the edge addition, then
      the edge was added to a hole in the array. */
   if(record_changes)
      pushAddedEdge(host_edge_index, edge_array_size1 == n_node_host->edges.size);
   /* Reset the morphism. */
   initialiseMorphism(morphism, n_node_host);
}

static bool fillpot_n2(MorphismPot *pot, Morphism *morphism);
static bool fillpot_n0(MorphismPot *pot, Morphism *morphism);
static bool fillpot_e0(MorphismPot *pot, Morphism *morphism);
static bool fillpot_n1(MorphismPot *pot, Morphism *morphism, Edge *host_edge);

bool fillpotn_node_propActive(MorphismPot *pot, Morphism *morphism)
{
   if(3 > n_node_host->number_of_nodes || 1 > n_node_host->number_of_edges) return false;
   int oldPotsize = potSize(pot);
   morphism->weight = 1.000000;
   fillpot_n2(pot, morphism);
   if(potSize(pot) > oldPotsize){
      initialiseMorphism(morphism, n_node_host);
      return true;
   }
   else
   {
      initialiseMorphism(morphism, n_node_host);
      return false;
   }
}

static bool fillpot_n2(MorphismPot *pot, Morphism *morphism)
{
   RootNodes *nodes;
   for(nodes = getRootNodeList(n_node_host); nodes != NULL; nodes = nodes->next)
   {
      Node *host_node = getNode(n_node_host, nodes->index);
      if(host_node == NULL) continue;
      if(host_node->matched) continue;
      if(host_node->label.mark != 4) continue;
      if(host_node->indegree < 0 || host_node->outdegree < 0 ||
         ((host_node->outdegree + host_node->indegree - 0 - 0 - 0) < 0)) continue;

      HostLabel label = host_node->label;
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
         if(item->atom.type != 's') break;
         else if(strcmp(item->atom.str, "Active") != 0) break;
         match = true;
      } while(false);

      if(match)
      {
         addNodeMap(morphism, 2, host_node->index, new_assignments);
         host_node->matched = true;
         /* Update global booleans representing the node's predicates. */
         evaluatePredicaten_node_1(morphism);
         bool next_match_result = false;
         if(evaluateCondition()) next_match_result = fillpot_n0(pot, morphism);
         if(next_match_result) return true;
         else
         {
            /* Reset the boolean variables in the predicates of this node. */
            n_node_b1 = false;
            removeNodeMap(morphism, 2);
            host_node->matched = false;
         }
      }
      else removeAssignments(morphism, new_assignments);
   }
   return false;
}

static bool fillpot_n0(MorphismPot *pot, Morphism *morphism)
{
   int host_index;
   for(host_index = 0; host_index < n_node_host->nodes.size; host_index++)
   {
      Node *host_node = getNode(n_node_host, host_index);
      if(host_node == NULL || host_node->index == -1) continue;
      if(host_node->matched) continue;
      if(host_node->label.mark != 0) continue;
      if(host_node->indegree < 0 || host_node->outdegree < 1 ||
         ((host_node->outdegree + host_node->indegree - 1 - 0 - 0) < 0)) continue;

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
   /* Start node is the already-matched node from which the candidate
      edges are drawn. End node may or may not have been matched already. */
   int start_index = lookupNode(morphism, 0);
   int end_index = lookupNode(morphism, 1);
   if(start_index < 0) return false;
   Node *host_node = getNode(n_node_host, start_index);

   int counter;
   for(counter = 0; counter < host_node->out_edges.size + 2; counter++)
   {
      Edge *host_edge = getNthOutEdge(n_node_host, host_node, counter);
      if(host_edge == NULL) continue;
      if(host_edge->matched) continue;
      if(host_edge->source == host_edge->target) continue;
      if(host_edge->label.mark != 0) continue;

      /* If the end node has been matched, check that the target of the
       * host edge is the image of the end node. */
      if(end_index >= 0)
      {
         if(host_edge->target != end_index) continue;
      }
      /* Otherwise, the target of the host edge should be unmatched. */
      else
      {
         Node *end_node = getNode(n_node_host, host_edge->target);
         if(end_node->matched) continue;
      }

      HostLabel label = host_edge->label;
      bool match = false;
      /* Label Matching */
      int new_assignments = 0;
      /* Match list variable 2 against the whole host list. */
      int result = -1;
      if(label.length == 1)
      {
         if(label.list->first->atom.type == 'i')
            result = addIntegerAssignment(morphism, 2, label.list->first->atom.num);
         else result = addStringAssignment(morphism, 2, label.list->first->atom.str);
      }
      else result = addListAssignment(morphism, 2, label.list);
      if(result >= 0)
      {
         new_assignments += result;
         match = true;
      }
      if(match)
      {
         addEdgeMap(morphism, 0, host_edge->index, new_assignments);
         host_edge->matched = true;
         if(fillpot_n1(pot, morphism, host_edge)) return true;
         else
         {
            removeEdgeMap(morphism, 0);
            host_edge->matched = false;
         }
      }
      else removeAssignments(morphism, new_assignments);
   }
   return false;
}

static bool fillpot_n1(MorphismPot *pot, Morphism *morphism, Edge *host_edge)
{
   Node *host_node = getTarget(n_node_host, host_edge);

   if(host_node->matched) return false;
   if(host_node->label.mark != 0) return false;
      if(host_node->indegree < 1 || host_node->outdegree < 0 ||
         ((host_node->outdegree + host_node->indegree - 0 - 1 - 0) < 0)) return false;;

   HostLabel label = host_node->label;
   bool match = false;
   /* Label Matching */
   int new_assignments = 0;
   /* Match list variable 1 against the whole host list. */
   int result = -1;
   if(label.length == 1)
   {
      if(label.list->first->atom.type == 'i')
         result = addIntegerAssignment(morphism, 1, label.list->first->atom.num);
      else result = addStringAssignment(morphism, 1, label.list->first->atom.str);
   }
   else result = addListAssignment(morphism, 1, label.list);
   if(result >= 0)
   {
      new_assignments += result;
      match = true;
   }
   if(match)
   {
      addNodeMap(morphism, 1, host_node->index, new_assignments);
      host_node->matched = true;
      /* Update global booleans representing the node's predicates. */
      evaluatePredicaten_node_1(morphism);
      if(evaluateCondition())
      {
         /* All items matched! */
         putMorphism(pot, morphism, "n_node_propActive", n_node_host);
         /* Reset the boolean variables in the predicates of this node. */
         n_node_b1 = false;
         removeNodeMap(morphism, 1);
         host_node->matched = false;
         return false;
      }
      else
      {
         /* Reset the boolean variables in the predicates of this node. */
         n_node_b1 = false;
         removeNodeMap(morphism, 1);
         host_node->matched = false;
      }
   }
   else removeAssignments(morphism, new_assignments);
   return false;
}


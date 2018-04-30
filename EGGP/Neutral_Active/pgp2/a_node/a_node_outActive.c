#include "a_node_outActive.h"

#include "a_node.h"

bool a_node_b0 = false;

static bool evaluateCondition(void)
{
   return (!a_node_b0);
}

static void evaluatePredicatea_node_0(Morphism *morphism)
{
   int n0 = lookupNode(morphism, 0);
   /* If the node is not yet matched by the morphism, return. */
   if(n0 == -1) return;

   int n1 = lookupNode(morphism, 1);
   /* If the node is not yet matched by the morphism, return. */
   if(n1 == -1) return;

   Node *source = getNode(a_node_host, n1);
   bool edge_found = false;
   int counter;
   for(counter = 0; counter < source->out_edges.size + 2; counter++)
   {
      Edge *edge = getNthOutEdge(a_node_host, source, counter);
      if(edge != NULL && edge->target == n0)
      {
         a_node_b0 = true;
         edge_found = true;
         break;
      }
   }
   if(!edge_found) a_node_b0 = false;
}

static bool match_n1(Morphism *morphism);
static bool match_n0(Morphism *morphism);

bool matcha_node_outActive(Morphism *morphism)
{
   if(2 > a_node_host->number_of_nodes || 0 > a_node_host->number_of_edges) return false;
   if(match_n1(morphism)) return true;
   else
   {
      initialiseMorphism(morphism, a_node_host);
      return false;
   }
}

static bool match_n1(Morphism *morphism)
{
   RootNodes *nodes;
   for(nodes = getRootNodeList(a_node_host); nodes != NULL; nodes = nodes->next)
   {
      Node *host_node = getNode(a_node_host, nodes->index);
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
         addNodeMap(morphism, 1, host_node->index, new_assignments);
         host_node->matched = true;
         /* Update global booleans representing the node's predicates. */
         evaluatePredicatea_node_0(morphism);
         bool next_match_result = false;
         if(evaluateCondition()) next_match_result = match_n0(morphism);
         if(next_match_result) return true;
         else
         {
            /* Reset the boolean variables in the predicates of this node. */
            a_node_b0 = false;
            removeNodeMap(morphism, 1);
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
   for(host_index = 0; host_index < a_node_host->nodes.size; host_index++)
   {
      Node *host_node = getNode(a_node_host, host_index);
      if(host_node == NULL || host_node->index == -1) continue;
      if(host_node->matched) continue;
      if(host_node->label.mark != 0) continue;
      if(host_node->indegree < 0 || host_node->outdegree < 0 ||
         ((host_node->outdegree + host_node->indegree - 0 - 0 - 0) < 0)) continue;

      HostLabel label = host_node->label;
      bool match = false;
      /* Label Matching */
      int new_assignments = 0;
      do
      {
         if(label.length < 1) break;
         /* Matching from the start of the host list. */
         HostListItem *item = label.list->first;
         int result = -1;
         HostListItem *start = item;
         /* The current host list position marks the start of the list that is
            assigned to the list variable. */
         /* More rule atoms to match. If the end of the host list is reached, break. */
         if(start == NULL) break;

         /* Matching from the end of the host list. */
         item = label.list->last;
         /* Check if the host list has passed "start". */
         if(item == start->prev) break;
         /* Matching rule atom 2 */
         if(item->atom.type != 's') break;
         else if(strcmp(item->atom.str, "OUT") != 0) break;
         item = item->prev;
         /* Matching list variable 0. */
         if(item == start->prev) result = addListAssignment(morphism, 0, NULL);
         else if(item == start)
         {
            if(item->atom.type == 'i') result = addIntegerAssignment(morphism, 0, item->atom.num);
            else result = addStringAssignment(morphism, 0, item->atom.str);
         }
         else
         {
            /* Assign to variable 0 the unmatched sublist of the host list. */
            HostAtom sublist[label.length - 1];
            int list_index = 0;
            HostListItem *iterator = start;
            while(iterator != item->next)
            {
               sublist[list_index++] = iterator->atom;
               iterator = iterator->next;
            }
            HostList *list = makeHostList(sublist, label.length - 1, false);
            result = addListAssignment(morphism, 0, list);
            freeHostList(list);
         }
         if(result >= 0)
         {
            new_assignments += result;
            match = true;
         }
      } while(false);

      if(match)
      {
         addNodeMap(morphism, 0, host_node->index, new_assignments);
         host_node->matched = true;
         /* Update global booleans representing the node's predicates. */
         evaluatePredicatea_node_0(morphism);
         if(evaluateCondition())
         {
            /* All items matched! */
            return true;
         }
         else
         {
            /* Reset the boolean variables in the predicates of this node. */
            a_node_b0 = false;
            removeNodeMap(morphism, 0);
            host_node->matched = false;
         }
      }
      else removeAssignments(morphism, new_assignments);
   }
   return false;
}

void applya_node_outActive(Morphism *morphism, bool record_changes)
{
   int host_edge_index;
   int source, target;
   int edge_array_size0 = a_node_host->edges.size;
   source = lookupNode(morphism, 1);
   target = lookupNode(morphism, 0);
   HostLabel label;
   label = makeEmptyLabel(5);

   host_edge_index = addEdge(a_node_host, label, source, target);
   /* If the edge array size has not increased after the edge addition, then
      the edge was added to a hole in the array. */
   if(record_changes)
      pushAddedEdge(host_edge_index, edge_array_size0 == a_node_host->edges.size);
   /* Reset the morphism. */
   initialiseMorphism(morphism, a_node_host);
}

static bool fillpot_n1(MorphismPot *pot, Morphism *morphism);
static bool fillpot_n0(MorphismPot *pot, Morphism *morphism);

bool fillpota_node_outActive(MorphismPot *pot, Morphism *morphism)
{
   if(2 > a_node_host->number_of_nodes || 0 > a_node_host->number_of_edges) return false;
   int oldPotsize = potSize(pot);
   morphism->weight = 1.000000;
   fillpot_n1(pot, morphism);
   if(potSize(pot) > oldPotsize){
      initialiseMorphism(morphism, a_node_host);
      return true;
   }
   else
   {
      initialiseMorphism(morphism, a_node_host);
      return false;
   }
}

static bool fillpot_n1(MorphismPot *pot, Morphism *morphism)
{
   RootNodes *nodes;
   for(nodes = getRootNodeList(a_node_host); nodes != NULL; nodes = nodes->next)
   {
      Node *host_node = getNode(a_node_host, nodes->index);
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
         addNodeMap(morphism, 1, host_node->index, new_assignments);
         host_node->matched = true;
         /* Update global booleans representing the node's predicates. */
         evaluatePredicatea_node_0(morphism);
         bool next_match_result = false;
         if(evaluateCondition()) next_match_result = fillpot_n0(pot, morphism);
         if(next_match_result) return true;
         else
         {
            /* Reset the boolean variables in the predicates of this node. */
            a_node_b0 = false;
            removeNodeMap(morphism, 1);
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
   for(host_index = 0; host_index < a_node_host->nodes.size; host_index++)
   {
      Node *host_node = getNode(a_node_host, host_index);
      if(host_node == NULL || host_node->index == -1) continue;
      if(host_node->matched) continue;
      if(host_node->label.mark != 0) continue;
      if(host_node->indegree < 0 || host_node->outdegree < 0 ||
         ((host_node->outdegree + host_node->indegree - 0 - 0 - 0) < 0)) continue;

      HostLabel label = host_node->label;
      bool match = false;
      /* Label Matching */
      int new_assignments = 0;
      do
      {
         if(label.length < 1) break;
         /* Matching from the start of the host list. */
         HostListItem *item = label.list->first;
         int result = -1;
         HostListItem *start = item;
         /* The current host list position marks the start of the list that is
            assigned to the list variable. */
         /* More rule atoms to match. If the end of the host list is reached, break. */
         if(start == NULL) break;

         /* Matching from the end of the host list. */
         item = label.list->last;
         /* Check if the host list has passed "start". */
         if(item == start->prev) break;
         /* Matching rule atom 2 */
         if(item->atom.type != 's') break;
         else if(strcmp(item->atom.str, "OUT") != 0) break;
         item = item->prev;
         /* Matching list variable 0. */
         if(item == start->prev) result = addListAssignment(morphism, 0, NULL);
         else if(item == start)
         {
            if(item->atom.type == 'i') result = addIntegerAssignment(morphism, 0, item->atom.num);
            else result = addStringAssignment(morphism, 0, item->atom.str);
         }
         else
         {
            /* Assign to variable 0 the unmatched sublist of the host list. */
            HostAtom sublist[label.length - 1];
            int list_index = 0;
            HostListItem *iterator = start;
            while(iterator != item->next)
            {
               sublist[list_index++] = iterator->atom;
               iterator = iterator->next;
            }
            HostList *list = makeHostList(sublist, label.length - 1, false);
            result = addListAssignment(morphism, 0, list);
            freeHostList(list);
         }
         if(result >= 0)
         {
            new_assignments += result;
            match = true;
         }
      } while(false);

      if(match)
      {
         addNodeMap(morphism, 0, host_node->index, new_assignments);
         host_node->matched = true;
         /* Update global booleans representing the node's predicates. */
         evaluatePredicatea_node_0(morphism);
         if(evaluateCondition())
         {
            /* All items matched! */
            putMorphism(pot, morphism, "a_node_outActive", a_node_host);
            /* Reset the boolean variables in the predicates of this node. */
            a_node_b0 = false;
            removeNodeMap(morphism, 0);
            host_node->matched = false;
            return false;
         }
         else
         {
            /* Reset the boolean variables in the predicates of this node. */
            a_node_b0 = false;
            removeNodeMap(morphism, 0);
            host_node->matched = false;
         }
      }
      else removeAssignments(morphism, new_assignments);
   }
   return false;
}


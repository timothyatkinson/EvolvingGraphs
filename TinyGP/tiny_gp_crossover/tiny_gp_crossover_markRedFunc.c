#include "tiny_gp_crossover_markRedFunc.h"

#include "tiny_gp_crossover.h"

bool tiny_gp_crossover_b0 = true;

static bool evaluateCondition(void)
{
   return (tiny_gp_crossover_b0);
}

static void evaluatePredicatetiny_gp_crossover_0(Morphism *morphism)
{
   Assignment assignment_3 = getAssignment(morphism, 3);
   /* If the variable is not yet assigned, return. */
   if(assignment_3.type == 'n') return;
   string var_3 = getStringValue(morphism, 3);

   int list_var_length0 = 0;
   int list_length0 = list_var_length0 + 1;
   HostAtom array0[list_length0];
   int index0 = 0;

   array0[index0].type = 's';
   array0[index0++].str = var_3;

   int list_var_length1 = 0;
   int list_length1 = list_var_length1 + 1;
   HostAtom array1[list_length1];
   int index1 = 0;

   array1[index1].type = 's';
   array1[index1++].str = "IN";

   if(!equalHostLists(array0, array1, list_length0, list_length1)) tiny_gp_crossover_b0 = true;
   else tiny_gp_crossover_b0 = false;
}

static bool match_n0(Morphism *morphism);
static bool match_e0(Morphism *morphism);
static bool match_n1(Morphism *morphism, Edge *host_edge);

bool matchtiny_gp_crossover_markRedFunc(Morphism *morphism)
{
   if(2 > tiny_gp_crossover_host->number_of_nodes || 1 > tiny_gp_crossover_host->number_of_edges) return false;
   if(match_n0(morphism)) return true;
   else
   {
      initialiseMorphism(morphism, tiny_gp_crossover_host);
      return false;
   }
}

static bool match_n0(Morphism *morphism)
{
   int host_index;
   for(host_index = 0; host_index < tiny_gp_crossover_host->nodes.size; host_index++)
   {
      Node *host_node = getNode(tiny_gp_crossover_host, host_index);
      if(host_node == NULL || host_node->index == -1) continue;
      if(host_node->matched) continue;
      if(host_node->label.mark != 1) continue;
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
   Node *host_node = getNode(tiny_gp_crossover_host, start_index);

   int counter;
   for(counter = 0; counter < host_node->out_edges.size + 2; counter++)
   {
      Edge *host_edge = getNthOutEdge(tiny_gp_crossover_host, host_node, counter);
      if(host_edge == NULL) continue;
      if(host_edge->matched) continue;
      if(host_edge->source == host_edge->target) continue;
      if(host_edge->label.mark != 1) continue;

      /* If the end node has been matched, check that the target of the
       * host edge is the image of the end node. */
      if(end_index >= 0)
      {
         if(host_edge->target != end_index) continue;
      }
      /* Otherwise, the target of the host edge should be unmatched. */
      else
      {
         Node *end_node = getNode(tiny_gp_crossover_host, host_edge->target);
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
   Node *host_node = getTarget(tiny_gp_crossover_host, host_edge);

   if(host_node->matched) return false;
   if(host_node->label.mark != 3) return false;
      if(host_node->indegree < 1 || host_node->outdegree < 0 ||
         ((host_node->outdegree + host_node->indegree - 0 - 1 - 0) < 0)) return false;;

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
      /* Matching string variable 3. */
      if(item->atom.type != 's') break;
      result = addStringAssignment(morphism, 3, item->atom.str);
      if(result >= 0)
      {
         new_assignments += result;
         /* Update global booleans for the variable's predicates. */
         evaluatePredicatetiny_gp_crossover_0(morphism);
         if(!evaluateCondition())
         {
            /* Reset the boolean variables in the predicates of this variable. */
            tiny_gp_crossover_b0 = true;
            break;
         }
      }
      else break;
      item = item->prev;
      /* Matching list variable 1. */
      if(item == start->prev) result = addListAssignment(morphism, 1, NULL);
      else if(item == start)
      {
         if(item->atom.type == 'i') result = addIntegerAssignment(morphism, 1, item->atom.num);
         else result = addStringAssignment(morphism, 1, item->atom.str);
      }
      else
      {
         /* Assign to variable 1 the unmatched sublist of the host list. */
         HostAtom sublist[label.length - 1];
         int list_index = 0;
         HostListItem *iterator = start;
         while(iterator != item->next)
         {
            sublist[list_index++] = iterator->atom;
            iterator = iterator->next;
         }
         HostList *list = makeHostList(sublist, label.length - 1, false);
         result = addListAssignment(morphism, 1, list);
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
      addNodeMap(morphism, 1, host_node->index, new_assignments);
      host_node->matched = true;
      /* All items matched! */
         return true;
   }
   else removeAssignments(morphism, new_assignments);
   return false;
}

void applytiny_gp_crossover_markRedFunc(Morphism *morphism, bool record_changes)
{
   int host_node_index = lookupNode(morphism, 1);
   HostLabel label_n1 = getNodeLabel(tiny_gp_crossover_host, host_node_index);
   if(record_changes) pushRemarkedNode(host_node_index, label_n1.mark);
   changeNodeMark(tiny_gp_crossover_host, host_node_index, 1);

   /* Reset the morphism. */
   initialiseMorphism(morphism, tiny_gp_crossover_host);
}

static bool fillpot_n0(MorphismPot *pot, Morphism *morphism);
static bool fillpot_e0(MorphismPot *pot, Morphism *morphism);
static bool fillpot_n1(MorphismPot *pot, Morphism *morphism, Edge *host_edge);

bool fillpottiny_gp_crossover_markRedFunc(MorphismPot *pot, Morphism *morphism)
{
   if(2 > tiny_gp_crossover_host->number_of_nodes || 1 > tiny_gp_crossover_host->number_of_edges) return false;
   int oldPotsize = potSize(pot);
   morphism->weight = 0.000000;
   fillpot_n0(pot, morphism);
   if(potSize(pot) > oldPotsize){
      initialiseMorphism(morphism, tiny_gp_crossover_host);
      return true;
   }
   else
   {
      initialiseMorphism(morphism, tiny_gp_crossover_host);
      return false;
   }
}

static bool fillpot_n0(MorphismPot *pot, Morphism *morphism)
{
   int host_index;
   for(host_index = 0; host_index < tiny_gp_crossover_host->nodes.size; host_index++)
   {
      Node *host_node = getNode(tiny_gp_crossover_host, host_index);
      if(host_node == NULL || host_node->index == -1) continue;
      if(host_node->matched) continue;
      if(host_node->label.mark != 1) continue;
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
   Node *host_node = getNode(tiny_gp_crossover_host, start_index);

   int counter;
   for(counter = 0; counter < host_node->out_edges.size + 2; counter++)
   {
      Edge *host_edge = getNthOutEdge(tiny_gp_crossover_host, host_node, counter);
      if(host_edge == NULL) continue;
      if(host_edge->matched) continue;
      if(host_edge->source == host_edge->target) continue;
      if(host_edge->label.mark != 1) continue;

      /* If the end node has been matched, check that the target of the
       * host edge is the image of the end node. */
      if(end_index >= 0)
      {
         if(host_edge->target != end_index) continue;
      }
      /* Otherwise, the target of the host edge should be unmatched. */
      else
      {
         Node *end_node = getNode(tiny_gp_crossover_host, host_edge->target);
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
   Node *host_node = getTarget(tiny_gp_crossover_host, host_edge);

   if(host_node->matched) return false;
   if(host_node->label.mark != 3) return false;
      if(host_node->indegree < 1 || host_node->outdegree < 0 ||
         ((host_node->outdegree + host_node->indegree - 0 - 1 - 0) < 0)) return false;;

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
      /* Matching string variable 3. */
      if(item->atom.type != 's') break;
      result = addStringAssignment(morphism, 3, item->atom.str);
      if(result >= 0)
      {
         new_assignments += result;
         /* Update global booleans for the variable's predicates. */
         evaluatePredicatetiny_gp_crossover_0(morphism);
         if(!evaluateCondition())
         {
            /* Reset the boolean variables in the predicates of this variable. */
            tiny_gp_crossover_b0 = true;
            break;
         }
      }
      else break;
      item = item->prev;
      /* Matching list variable 1. */
      if(item == start->prev) result = addListAssignment(morphism, 1, NULL);
      else if(item == start)
      {
         if(item->atom.type == 'i') result = addIntegerAssignment(morphism, 1, item->atom.num);
         else result = addStringAssignment(morphism, 1, item->atom.str);
      }
      else
      {
         /* Assign to variable 1 the unmatched sublist of the host list. */
         HostAtom sublist[label.length - 1];
         int list_index = 0;
         HostListItem *iterator = start;
         while(iterator != item->next)
         {
            sublist[list_index++] = iterator->atom;
            iterator = iterator->next;
         }
         HostList *list = makeHostList(sublist, label.length - 1, false);
         result = addListAssignment(morphism, 1, list);
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
      addNodeMap(morphism, 1, host_node->index, new_assignments);
      host_node->matched = true;
      /* All items matched! */
         putMorphism(pot, morphism, "tiny_gp_crossover_markRedFunc", tiny_gp_crossover_host);
         removeNodeMap(morphism, 1);
         host_node->matched = false;
   }
   else removeAssignments(morphism, new_assignments);
   return false;
}


#include "eggp_dc_init_updateDepth.h"

#include "eggp_dc_init.h"

bool eggp_dc_init_b4 = true;

static bool evaluateCondition(void)
{
   return (eggp_dc_init_b4);
}

static void evaluatePredicateeggp_dc_init_4(Morphism *morphism)
{
   Assignment assignment_4 = getAssignment(morphism, 4);
   /* If the variable is not yet assigned, return. */
   if(assignment_4.type == 'n') return;
   int var_4 = getIntegerValue(morphism, 4);

   Assignment assignment_5 = getAssignment(morphism, 5);
   /* If the variable is not yet assigned, return. */
   if(assignment_5.type == 'n') return;
   int var_5 = getIntegerValue(morphism, 5);

   if(var_4 < var_5 + 1) eggp_dc_init_b4 = true;
   else eggp_dc_init_b4 = false;
}

static bool match_n0(Morphism *morphism);
static bool match_e0(Morphism *morphism);
static bool match_n1(Morphism *morphism, Edge *host_edge);

bool matcheggp_dc_init_updateDepth(Morphism *morphism)
{
   if(2 > eggp_dc_init_host->number_of_nodes || 1 > eggp_dc_init_host->number_of_edges) return false;
   if(match_n0(morphism)) return true;
   else
   {
      initialiseMorphism(morphism, eggp_dc_init_host);
      return false;
   }
}

static bool match_n0(Morphism *morphism)
{
   int host_index;
   for(host_index = 0; host_index < eggp_dc_init_host->nodes.size; host_index++)
   {
      Node *host_node = getNode(eggp_dc_init_host, host_index);
      if(host_node == NULL || host_node->index == -1) continue;
      if(host_node->matched) continue;
      if(host_node->label.mark != 1) continue;
      if(host_node->indegree < 0 || host_node->outdegree < 1 ||
         ((host_node->outdegree + host_node->indegree - 1 - 0 - 0) < 0)) continue;

      HostLabel label = host_node->label;
      bool match = false;
      /* Label Matching */
      int new_assignments = 0;
      do
      {
         if(label.length < 2) break;
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
         /* Matching rule atom 3 */
         /* Matching string variable 2. */
         if(item->atom.type != 's') break;
         result = addStringAssignment(morphism, 2, item->atom.str);
         if(result >= 0)
         {
            new_assignments += result;
         }
         else break;
         item = item->prev;
         /* Check if the host list has passed "start". */
         if(item == start->prev) break;
         /* Matching rule atom 2 */
         /* Matching integer variable 4. */
         if(item->atom.type != 'i') break;
         result = addIntegerAssignment(morphism, 4, item->atom.num);
         if(result >= 0)
         {
            new_assignments += result;
            /* Update global booleans for the variable's predicates. */
            evaluatePredicateeggp_dc_init_4(morphism);
            if(!evaluateCondition())
            {
               /* Reset the boolean variables in the predicates of this variable. */
               eggp_dc_init_b4 = true;
               break;
            }
         }
         else break;
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
            HostAtom sublist[label.length - 2];
            int list_index = 0;
            HostListItem *iterator = start;
            while(iterator != item->next)
            {
               sublist[list_index++] = iterator->atom;
               iterator = iterator->next;
            }
            HostList *list = makeHostList(sublist, label.length - 2, false);
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
   Node *host_node = getNode(eggp_dc_init_host, start_index);

   int counter;
   for(counter = 0; counter < host_node->out_edges.size + 2; counter++)
   {
      Edge *host_edge = getNthOutEdge(eggp_dc_init_host, host_node, counter);
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
         Node *end_node = getNode(eggp_dc_init_host, host_edge->target);
         if(end_node->matched) continue;
      }

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
         /* Matching integer variable 6. */
         if(item->atom.type != 'i') break;
         result = addIntegerAssignment(morphism, 6, item->atom.num);
         if(result >= 0)
         {
            new_assignments += result;
         }
         else break;
         match = true;
      } while(false);

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
   Node *host_node = getTarget(eggp_dc_init_host, host_edge);

   if(host_node->matched) return false;
   if(host_node->label.mark != 0) return false;
      if(host_node->indegree < 1 || host_node->outdegree < 0 ||
         ((host_node->outdegree + host_node->indegree - 0 - 1 - 0) < 0)) return false;;

   HostLabel label = host_node->label;
   bool match = false;
   /* Label Matching */
   int new_assignments = 0;
   do
   {
      if(label.length < 2) break;
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
      /* Matching rule atom 3 */
      /* Matching string variable 3. */
      if(item->atom.type != 's') break;
      result = addStringAssignment(morphism, 3, item->atom.str);
      if(result >= 0)
      {
         new_assignments += result;
      }
      else break;
      item = item->prev;
      /* Check if the host list has passed "start". */
      if(item == start->prev) break;
      /* Matching rule atom 2 */
      /* Matching integer variable 5. */
      if(item->atom.type != 'i') break;
      result = addIntegerAssignment(morphism, 5, item->atom.num);
      if(result >= 0)
      {
         new_assignments += result;
         /* Update global booleans for the variable's predicates. */
         evaluatePredicateeggp_dc_init_4(morphism);
         if(!evaluateCondition())
         {
            /* Reset the boolean variables in the predicates of this variable. */
            eggp_dc_init_b4 = true;
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
         HostAtom sublist[label.length - 2];
         int list_index = 0;
         HostListItem *iterator = start;
         while(iterator != item->next)
         {
            sublist[list_index++] = iterator->atom;
            iterator = iterator->next;
         }
         HostList *list = makeHostList(sublist, label.length - 2, false);
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

void applyeggp_dc_init_updateDepth(Morphism *morphism, bool record_changes)
{
   Assignment var_0 = getAssignment(morphism, 0);
   string var_2 = getStringValue(morphism, 2);
   int var_5 = getIntegerValue(morphism, 5);
   int host_node_index = lookupNode(morphism, 0);
   HostLabel label_n0 = getNodeLabel(eggp_dc_init_host, host_node_index);
   HostLabel label;
   int list_var_length0 = 0;
   list_var_length0 += getAssignmentLength(var_0);
   int list_length0 = list_var_length0 + 2;
   HostAtom array0[list_length0];
   int index0 = 0;

   if(var_0.type == 'l' && var_0.list != NULL)
   {
      HostListItem *item0 = var_0.list->first;
      while(item0 != NULL)
      {
         array0[index0++] = item0->atom;
         item0 = item0->next;
      }
   }
   else if(var_0.type == 'i')
   {
      array0[index0].type = 'i';
      array0[index0++].num = var_0.num;
   }
   else if(var_0.type == 's')
   {
      array0[index0].type = 's';
      array0[index0++].str = var_0.str;
   }

   array0[index0].type = 'i';
   array0[index0++].num = var_5 + 1;
   array0[index0].type = 's';
   array0[index0++].str = var_2;
   if(list_length0 > 0)
   {
      HostList *list0 = makeHostList(array0, list_length0, false);
      label = makeHostLabel(1, list_length0, list0);
   }
   else label = makeEmptyLabel(1);

   if(equalHostLabels(label_n0, label)) removeHostList(label.list);
   else
   {
      if(record_changes) pushRelabelledNode(host_node_index, label_n0);
      relabelNode(eggp_dc_init_host, host_node_index, label);
   }
   /* Reset the morphism. */
   initialiseMorphism(morphism, eggp_dc_init_host);
}

static bool fillpot_n0(MorphismPot *pot, Morphism *morphism);
static bool fillpot_e0(MorphismPot *pot, Morphism *morphism);
static bool fillpot_n1(MorphismPot *pot, Morphism *morphism, Edge *host_edge);

bool fillpoteggp_dc_init_updateDepth(MorphismPot *pot, Morphism *morphism)
{
   if(2 > eggp_dc_init_host->number_of_nodes || 1 > eggp_dc_init_host->number_of_edges) return false;
   int oldPotsize = potSize(pot);
   morphism->weight = 1.000000;
   fillpot_n0(pot, morphism);
   if(potSize(pot) > oldPotsize){
      initialiseMorphism(morphism, eggp_dc_init_host);
      return true;
   }
   else
   {
      initialiseMorphism(morphism, eggp_dc_init_host);
      return false;
   }
}

static bool fillpot_n0(MorphismPot *pot, Morphism *morphism)
{
   int host_index;
   for(host_index = 0; host_index < eggp_dc_init_host->nodes.size; host_index++)
   {
      Node *host_node = getNode(eggp_dc_init_host, host_index);
      if(host_node == NULL || host_node->index == -1) continue;
      if(host_node->matched) continue;
      if(host_node->label.mark != 1) continue;
      if(host_node->indegree < 0 || host_node->outdegree < 1 ||
         ((host_node->outdegree + host_node->indegree - 1 - 0 - 0) < 0)) continue;

      HostLabel label = host_node->label;
      bool match = false;
      /* Label Matching */
      int new_assignments = 0;
      do
      {
         if(label.length < 2) break;
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
         /* Matching rule atom 3 */
         /* Matching string variable 2. */
         if(item->atom.type != 's') break;
         result = addStringAssignment(morphism, 2, item->atom.str);
         if(result >= 0)
         {
            new_assignments += result;
         }
         else break;
         item = item->prev;
         /* Check if the host list has passed "start". */
         if(item == start->prev) break;
         /* Matching rule atom 2 */
         /* Matching integer variable 4. */
         if(item->atom.type != 'i') break;
         result = addIntegerAssignment(morphism, 4, item->atom.num);
         if(result >= 0)
         {
            new_assignments += result;
            /* Update global booleans for the variable's predicates. */
            evaluatePredicateeggp_dc_init_4(morphism);
            if(!evaluateCondition())
            {
               /* Reset the boolean variables in the predicates of this variable. */
               eggp_dc_init_b4 = true;
               break;
            }
         }
         else break;
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
            HostAtom sublist[label.length - 2];
            int list_index = 0;
            HostListItem *iterator = start;
            while(iterator != item->next)
            {
               sublist[list_index++] = iterator->atom;
               iterator = iterator->next;
            }
            HostList *list = makeHostList(sublist, label.length - 2, false);
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
   Node *host_node = getNode(eggp_dc_init_host, start_index);

   int counter;
   for(counter = 0; counter < host_node->out_edges.size + 2; counter++)
   {
      Edge *host_edge = getNthOutEdge(eggp_dc_init_host, host_node, counter);
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
         Node *end_node = getNode(eggp_dc_init_host, host_edge->target);
         if(end_node->matched) continue;
      }

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
         /* Matching integer variable 6. */
         if(item->atom.type != 'i') break;
         result = addIntegerAssignment(morphism, 6, item->atom.num);
         if(result >= 0)
         {
            new_assignments += result;
         }
         else break;
         match = true;
      } while(false);

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
   Node *host_node = getTarget(eggp_dc_init_host, host_edge);

   if(host_node->matched) return false;
   if(host_node->label.mark != 0) return false;
      if(host_node->indegree < 1 || host_node->outdegree < 0 ||
         ((host_node->outdegree + host_node->indegree - 0 - 1 - 0) < 0)) return false;;

   HostLabel label = host_node->label;
   bool match = false;
   /* Label Matching */
   int new_assignments = 0;
   do
   {
      if(label.length < 2) break;
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
      /* Matching rule atom 3 */
      /* Matching string variable 3. */
      if(item->atom.type != 's') break;
      result = addStringAssignment(morphism, 3, item->atom.str);
      if(result >= 0)
      {
         new_assignments += result;
      }
      else break;
      item = item->prev;
      /* Check if the host list has passed "start". */
      if(item == start->prev) break;
      /* Matching rule atom 2 */
      /* Matching integer variable 5. */
      if(item->atom.type != 'i') break;
      result = addIntegerAssignment(morphism, 5, item->atom.num);
      if(result >= 0)
      {
         new_assignments += result;
         /* Update global booleans for the variable's predicates. */
         evaluatePredicateeggp_dc_init_4(morphism);
         if(!evaluateCondition())
         {
            /* Reset the boolean variables in the predicates of this variable. */
            eggp_dc_init_b4 = true;
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
         HostAtom sublist[label.length - 2];
         int list_index = 0;
         HostListItem *iterator = start;
         while(iterator != item->next)
         {
            sublist[list_index++] = iterator->atom;
            iterator = iterator->next;
         }
         HostList *list = makeHostList(sublist, label.length - 2, false);
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
         putMorphism(pot, morphism, "eggp_dc_init_updateDepth", eggp_dc_init_host);
         removeNodeMap(morphism, 1);
         host_node->matched = false;
   }
   else removeAssignments(morphism, new_assignments);
   return false;
}


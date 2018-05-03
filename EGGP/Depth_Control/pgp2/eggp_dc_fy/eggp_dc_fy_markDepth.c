#include "eggp_dc_fy_markDepth.h"

#include "eggp_dc_fy.h"

bool eggp_dc_fy_b3 = true;
bool eggp_dc_fy_b4 = true;

static bool evaluateCondition(void)
{
   return (eggp_dc_fy_b3 && eggp_dc_fy_b4);
}

static void evaluatePredicateeggp_dc_fy_3(Morphism *morphism)
{
   Assignment assignment_4 = getAssignment(morphism, 4);
   /* If the variable is not yet assigned, return. */
   if(assignment_4.type == 'n') return;
   string var_4 = getStringValue(morphism, 4);

   int list_var_length0 = 0;
   int list_length0 = list_var_length0 + 1;
   HostAtom array0[list_length0];
   int index0 = 0;

   array0[index0].type = 's';
   array0[index0++].str = var_4;

   int list_var_length1 = 0;
   int list_length1 = list_var_length1 + 1;
   HostAtom array1[list_length1];
   int index1 = 0;

   array1[index1].type = 's';
   array1[index1++].str = "OUT";

   if(!equalHostLists(array0, array1, list_length0, list_length1)) eggp_dc_fy_b3 = true;
   else eggp_dc_fy_b3 = false;
}

static void evaluatePredicateeggp_dc_fy_4(Morphism *morphism)
{
   Assignment assignment_7 = getAssignment(morphism, 7);
   /* If the variable is not yet assigned, return. */
   if(assignment_7.type == 'n') return;
   int var_7 = getIntegerValue(morphism, 7);

   Assignment assignment_8 = getAssignment(morphism, 8);
   /* If the variable is not yet assigned, return. */
   if(assignment_8.type == 'n') return;
   int var_8 = getIntegerValue(morphism, 8);

   Assignment assignment_10 = getAssignment(morphism, 10);
   /* If the variable is not yet assigned, return. */
   if(assignment_10.type == 'n') return;
   int var_10 = getIntegerValue(morphism, 10);

   if(var_7 + var_8 > var_10) eggp_dc_fy_b4 = true;
   else eggp_dc_fy_b4 = false;
}

static bool match_n2(Morphism *morphism);
static bool match_n0(Morphism *morphism);
static bool match_n1(Morphism *morphism);

bool matcheggp_dc_fy_markDepth(Morphism *morphism)
{
   if(3 > eggp_dc_fy_host->number_of_nodes || 0 > eggp_dc_fy_host->number_of_edges) return false;
   if(match_n2(morphism)) return true;
   else
   {
      initialiseMorphism(morphism, eggp_dc_fy_host);
      return false;
   }
}

static bool match_n2(Morphism *morphism)
{
   RootNodes *nodes;
   for(nodes = getRootNodeList(eggp_dc_fy_host); nodes != NULL; nodes = nodes->next)
   {
      Node *host_node = getNode(eggp_dc_fy_host, nodes->index);
      if(host_node == NULL) continue;
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
         /* The rule list does not contain a list variable, so there is no
          * match if the host list has a different length. */
         if(label.length != 2) break;
         HostListItem *item = label.list->first;
         /* Matching rule atom 1. */
         if(item->atom.type != 's') break;
         else if(strcmp(item->atom.str, "Depth") != 0) break;
         item = item->next;

         /* Matching rule atom 2. */
         int result = -1;
         /* Matching integer variable 10. */
         if(item->atom.type != 'i') break;
         result = addIntegerAssignment(morphism, 10, item->atom.num);
         if(result >= 0)
         {
            new_assignments += result;
            /* Update global booleans for the variable's predicates. */
            evaluatePredicateeggp_dc_fy_4(morphism);
            if(!evaluateCondition())
            {
               /* Reset the boolean variables in the predicates of this variable. */
               eggp_dc_fy_b4 = true;
               break;
            }
         }
         else break;
         match = true;
      } while(false);

      if(match)
      {
         addNodeMap(morphism, 2, host_node->index, new_assignments);
         host_node->matched = true;
         if(match_n0(morphism)) return true;
         else
         {
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
   for(host_index = 0; host_index < eggp_dc_fy_host->nodes.size; host_index++)
   {
      Node *host_node = getNode(eggp_dc_fy_host, host_index);
      if(host_node == NULL || host_node->index == -1) continue;
      if(host_node->matched) continue;
      if(host_node->label.mark != 1) continue;
      if(host_node->indegree < 0 || host_node->outdegree < 0 ||
         ((host_node->outdegree + host_node->indegree - 0 - 0 - 0) < 0)) continue;

      HostLabel label = host_node->label;
      bool match = false;
      /* Label Matching */
      int new_assignments = 0;
      do
      {
         if(label.length < 3) break;
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
         /* Matching rule atom 4 */
         /* Matching string variable 4. */
         if(item->atom.type != 's') break;
         result = addStringAssignment(morphism, 4, item->atom.str);
         if(result >= 0)
         {
            new_assignments += result;
            /* Update global booleans for the variable's predicates. */
            evaluatePredicateeggp_dc_fy_3(morphism);
            if(!evaluateCondition())
            {
               /* Reset the boolean variables in the predicates of this variable. */
               eggp_dc_fy_b3 = true;
               break;
            }
         }
         else break;
         item = item->prev;
         /* Check if the host list has passed "start". */
         if(item == start->prev) break;
         /* Matching rule atom 3 */
         /* Matching integer variable 7. */
         if(item->atom.type != 'i') break;
         result = addIntegerAssignment(morphism, 7, item->atom.num);
         if(result >= 0)
         {
            new_assignments += result;
            /* Update global booleans for the variable's predicates. */
            evaluatePredicateeggp_dc_fy_4(morphism);
            if(!evaluateCondition())
            {
               /* Reset the boolean variables in the predicates of this variable. */
               eggp_dc_fy_b4 = true;
               break;
            }
         }
         else break;
         item = item->prev;
         /* Check if the host list has passed "start". */
         if(item == start->prev) break;
         /* Matching rule atom 2 */
         /* Matching integer variable 6. */
         if(item->atom.type != 'i') break;
         result = addIntegerAssignment(morphism, 6, item->atom.num);
         if(result >= 0)
         {
            new_assignments += result;
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
            HostAtom sublist[label.length - 3];
            int list_index = 0;
            HostListItem *iterator = start;
            while(iterator != item->next)
            {
               sublist[list_index++] = iterator->atom;
               iterator = iterator->next;
            }
            HostList *list = makeHostList(sublist, label.length - 3, false);
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
         if(match_n1(morphism)) return true;
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

static bool match_n1(Morphism *morphism)
{
   int host_index;
   for(host_index = 0; host_index < eggp_dc_fy_host->nodes.size; host_index++)
   {
      Node *host_node = getNode(eggp_dc_fy_host, host_index);
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
         if(label.length < 3) break;
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
         /* Matching rule atom 4 */
         /* Matching string variable 5. */
         if(item->atom.type != 's') break;
         result = addStringAssignment(morphism, 5, item->atom.str);
         if(result >= 0)
         {
            new_assignments += result;
         }
         else break;
         item = item->prev;
         /* Check if the host list has passed "start". */
         if(item == start->prev) break;
         /* Matching rule atom 3 */
         /* Matching integer variable 9. */
         if(item->atom.type != 'i') break;
         result = addIntegerAssignment(morphism, 9, item->atom.num);
         if(result >= 0)
         {
            new_assignments += result;
         }
         else break;
         item = item->prev;
         /* Check if the host list has passed "start". */
         if(item == start->prev) break;
         /* Matching rule atom 2 */
         /* Matching integer variable 8. */
         if(item->atom.type != 'i') break;
         result = addIntegerAssignment(morphism, 8, item->atom.num);
         if(result >= 0)
         {
            new_assignments += result;
            /* Update global booleans for the variable's predicates. */
            evaluatePredicateeggp_dc_fy_4(morphism);
            if(!evaluateCondition())
            {
               /* Reset the boolean variables in the predicates of this variable. */
               eggp_dc_fy_b4 = true;
               break;
            }
         }
         else break;
         item = item->prev;
         /* Matching list variable 3. */
         if(item == start->prev) result = addListAssignment(morphism, 3, NULL);
         else if(item == start)
         {
            if(item->atom.type == 'i') result = addIntegerAssignment(morphism, 3, item->atom.num);
            else result = addStringAssignment(morphism, 3, item->atom.str);
         }
         else
         {
            /* Assign to variable 3 the unmatched sublist of the host list. */
            HostAtom sublist[label.length - 3];
            int list_index = 0;
            HostListItem *iterator = start;
            while(iterator != item->next)
            {
               sublist[list_index++] = iterator->atom;
               iterator = iterator->next;
            }
            HostList *list = makeHostList(sublist, label.length - 3, false);
            result = addListAssignment(morphism, 3, list);
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
   }
   return false;
}

void applyeggp_dc_fy_markDepth(Morphism *morphism, bool record_changes)
{
   int host_node_index = lookupNode(morphism, 1);
   HostLabel label_n1 = getNodeLabel(eggp_dc_fy_host, host_node_index);
   if(record_changes) pushRemarkedNode(host_node_index, label_n1.mark);
   changeNodeMark(eggp_dc_fy_host, host_node_index, 3);

   /* Reset the morphism. */
   initialiseMorphism(morphism, eggp_dc_fy_host);
}

static bool fillpot_n2(MorphismPot *pot, Morphism *morphism);
static bool fillpot_n0(MorphismPot *pot, Morphism *morphism);
static bool fillpot_n1(MorphismPot *pot, Morphism *morphism);

bool fillpoteggp_dc_fy_markDepth(MorphismPot *pot, Morphism *morphism)
{
   if(3 > eggp_dc_fy_host->number_of_nodes || 0 > eggp_dc_fy_host->number_of_edges) return false;
   int oldPotsize = potSize(pot);
   morphism->weight = 1.000000;
   fillpot_n2(pot, morphism);
   if(potSize(pot) > oldPotsize){
      initialiseMorphism(morphism, eggp_dc_fy_host);
      return true;
   }
   else
   {
      initialiseMorphism(morphism, eggp_dc_fy_host);
      return false;
   }
}

static bool fillpot_n2(MorphismPot *pot, Morphism *morphism)
{
   RootNodes *nodes;
   for(nodes = getRootNodeList(eggp_dc_fy_host); nodes != NULL; nodes = nodes->next)
   {
      Node *host_node = getNode(eggp_dc_fy_host, nodes->index);
      if(host_node == NULL) continue;
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
         /* The rule list does not contain a list variable, so there is no
          * match if the host list has a different length. */
         if(label.length != 2) break;
         HostListItem *item = label.list->first;
         /* Matching rule atom 1. */
         if(item->atom.type != 's') break;
         else if(strcmp(item->atom.str, "Depth") != 0) break;
         item = item->next;

         /* Matching rule atom 2. */
         int result = -1;
         /* Matching integer variable 10. */
         if(item->atom.type != 'i') break;
         result = addIntegerAssignment(morphism, 10, item->atom.num);
         if(result >= 0)
         {
            new_assignments += result;
            /* Update global booleans for the variable's predicates. */
            evaluatePredicateeggp_dc_fy_4(morphism);
            if(!evaluateCondition())
            {
               /* Reset the boolean variables in the predicates of this variable. */
               eggp_dc_fy_b4 = true;
               break;
            }
         }
         else break;
         match = true;
      } while(false);

      if(match)
      {
         addNodeMap(morphism, 2, host_node->index, new_assignments);
         host_node->matched = true;
         if(fillpot_n0(pot, morphism)) return true;
         else
         {
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
   for(host_index = 0; host_index < eggp_dc_fy_host->nodes.size; host_index++)
   {
      Node *host_node = getNode(eggp_dc_fy_host, host_index);
      if(host_node == NULL || host_node->index == -1) continue;
      if(host_node->matched) continue;
      if(host_node->label.mark != 1) continue;
      if(host_node->indegree < 0 || host_node->outdegree < 0 ||
         ((host_node->outdegree + host_node->indegree - 0 - 0 - 0) < 0)) continue;

      HostLabel label = host_node->label;
      bool match = false;
      /* Label Matching */
      int new_assignments = 0;
      do
      {
         if(label.length < 3) break;
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
         /* Matching rule atom 4 */
         /* Matching string variable 4. */
         if(item->atom.type != 's') break;
         result = addStringAssignment(morphism, 4, item->atom.str);
         if(result >= 0)
         {
            new_assignments += result;
            /* Update global booleans for the variable's predicates. */
            evaluatePredicateeggp_dc_fy_3(morphism);
            if(!evaluateCondition())
            {
               /* Reset the boolean variables in the predicates of this variable. */
               eggp_dc_fy_b3 = true;
               break;
            }
         }
         else break;
         item = item->prev;
         /* Check if the host list has passed "start". */
         if(item == start->prev) break;
         /* Matching rule atom 3 */
         /* Matching integer variable 7. */
         if(item->atom.type != 'i') break;
         result = addIntegerAssignment(morphism, 7, item->atom.num);
         if(result >= 0)
         {
            new_assignments += result;
            /* Update global booleans for the variable's predicates. */
            evaluatePredicateeggp_dc_fy_4(morphism);
            if(!evaluateCondition())
            {
               /* Reset the boolean variables in the predicates of this variable. */
               eggp_dc_fy_b4 = true;
               break;
            }
         }
         else break;
         item = item->prev;
         /* Check if the host list has passed "start". */
         if(item == start->prev) break;
         /* Matching rule atom 2 */
         /* Matching integer variable 6. */
         if(item->atom.type != 'i') break;
         result = addIntegerAssignment(morphism, 6, item->atom.num);
         if(result >= 0)
         {
            new_assignments += result;
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
            HostAtom sublist[label.length - 3];
            int list_index = 0;
            HostListItem *iterator = start;
            while(iterator != item->next)
            {
               sublist[list_index++] = iterator->atom;
               iterator = iterator->next;
            }
            HostList *list = makeHostList(sublist, label.length - 3, false);
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
         if(fillpot_n1(pot, morphism)) return true;
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

static bool fillpot_n1(MorphismPot *pot, Morphism *morphism)
{
   int host_index;
   for(host_index = 0; host_index < eggp_dc_fy_host->nodes.size; host_index++)
   {
      Node *host_node = getNode(eggp_dc_fy_host, host_index);
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
         if(label.length < 3) break;
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
         /* Matching rule atom 4 */
         /* Matching string variable 5. */
         if(item->atom.type != 's') break;
         result = addStringAssignment(morphism, 5, item->atom.str);
         if(result >= 0)
         {
            new_assignments += result;
         }
         else break;
         item = item->prev;
         /* Check if the host list has passed "start". */
         if(item == start->prev) break;
         /* Matching rule atom 3 */
         /* Matching integer variable 9. */
         if(item->atom.type != 'i') break;
         result = addIntegerAssignment(morphism, 9, item->atom.num);
         if(result >= 0)
         {
            new_assignments += result;
         }
         else break;
         item = item->prev;
         /* Check if the host list has passed "start". */
         if(item == start->prev) break;
         /* Matching rule atom 2 */
         /* Matching integer variable 8. */
         if(item->atom.type != 'i') break;
         result = addIntegerAssignment(morphism, 8, item->atom.num);
         if(result >= 0)
         {
            new_assignments += result;
            /* Update global booleans for the variable's predicates. */
            evaluatePredicateeggp_dc_fy_4(morphism);
            if(!evaluateCondition())
            {
               /* Reset the boolean variables in the predicates of this variable. */
               eggp_dc_fy_b4 = true;
               break;
            }
         }
         else break;
         item = item->prev;
         /* Matching list variable 3. */
         if(item == start->prev) result = addListAssignment(morphism, 3, NULL);
         else if(item == start)
         {
            if(item->atom.type == 'i') result = addIntegerAssignment(morphism, 3, item->atom.num);
            else result = addStringAssignment(morphism, 3, item->atom.str);
         }
         else
         {
            /* Assign to variable 3 the unmatched sublist of the host list. */
            HostAtom sublist[label.length - 3];
            int list_index = 0;
            HostListItem *iterator = start;
            while(iterator != item->next)
            {
               sublist[list_index++] = iterator->atom;
               iterator = iterator->next;
            }
            HostList *list = makeHostList(sublist, label.length - 3, false);
            result = addListAssignment(morphism, 3, list);
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
            putMorphism(pot, morphism, "eggp_dc_fy_markDepth", eggp_dc_fy_host);
            removeNodeMap(morphism, 1);
            host_node->matched = false;
      }
      else removeAssignments(morphism, new_assignments);
   }
   return false;
}


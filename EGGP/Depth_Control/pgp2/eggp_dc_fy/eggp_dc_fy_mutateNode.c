#include "eggp_dc_fy_mutateNode.h"

#include "eggp_dc_fy.h"

bool eggp_dc_fy_b2 = true;

static bool evaluateCondition(void)
{
   return (eggp_dc_fy_b2);
}

static void evaluatePredicateeggp_dc_fy_2(Morphism *morphism)
{
   Assignment assignment_1 = getAssignment(morphism, 1);
   /* If the variable is not yet assigned, return. */
   if(assignment_1.type == 'n') return;
   string var_1 = getStringValue(morphism, 1);

   Assignment assignment_2 = getAssignment(morphism, 2);
   /* If the variable is not yet assigned, return. */
   if(assignment_2.type == 'n') return;
   string var_2 = getStringValue(morphism, 2);

   int list_var_length0 = 0;
   int list_length0 = list_var_length0 + 1;
   HostAtom array0[list_length0];
   int index0 = 0;

   array0[index0].type = 's';
   array0[index0++].str = var_1;

   int list_var_length1 = 0;
   int list_length1 = list_var_length1 + 1;
   HostAtom array1[list_length1];
   int index1 = 0;

   array1[index1].type = 's';
   array1[index1++].str = var_2;

   if(!equalHostLists(array0, array1, list_length0, list_length1)) eggp_dc_fy_b2 = true;
   else eggp_dc_fy_b2 = false;
}

static bool match_n1(Morphism *morphism);
static bool match_n0(Morphism *morphism);

bool matcheggp_dc_fy_mutateNode(Morphism *morphism)
{
   if(2 > eggp_dc_fy_host->number_of_nodes || 0 > eggp_dc_fy_host->number_of_edges) return false;
   if(match_n1(morphism)) return true;
   else
   {
      initialiseMorphism(morphism, eggp_dc_fy_host);
      return false;
   }
}

static bool match_n1(Morphism *morphism)
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
         if(label.length != 3) break;
         HostListItem *item = label.list->first;
         /* Matching rule atom 1. */
         if(item->atom.type != 's') break;
         else if(strcmp(item->atom.str, "FunctionSet") != 0) break;
         item = item->next;

         /* Matching rule atom 2. */
         int result = -1;
         /* Matching string variable 2. */
         if(item->atom.type != 's') break;
         result = addStringAssignment(morphism, 2, item->atom.str);
         if(result >= 0)
         {
            new_assignments += result;
            /* Update global booleans for the variable's predicates. */
            evaluatePredicateeggp_dc_fy_2(morphism);
            if(!evaluateCondition())
            {
               /* Reset the boolean variables in the predicates of this variable. */
               eggp_dc_fy_b2 = true;
               break;
            }
         }
         else break;
         item = item->next;

         /* Matching rule atom 3. */
         /* Matching integer variable 3. */
         if(item->atom.type != 'i') break;
         result = addIntegerAssignment(morphism, 3, item->atom.num);
         if(result >= 0)
         {
            new_assignments += result;
         }
         else break;
         match = true;
      } while(false);

      if(match)
      {
         addNodeMap(morphism, 1, host_node->index, new_assignments);
         host_node->matched = true;
         if(match_n0(morphism)) return true;
         else
         {
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
   for(host_index = 0; host_index < eggp_dc_fy_host->nodes.size; host_index++)
   {
      Node *host_node = getNode(eggp_dc_fy_host, host_index);
      if(host_node == NULL || host_node->index == -1) continue;
      if(host_node->matched) continue;
      if(host_node->label.mark != 3) continue;
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
         /* Matching string variable 1. */
         if(item->atom.type != 's') break;
         result = addStringAssignment(morphism, 1, item->atom.str);
         if(result >= 0)
         {
            new_assignments += result;
            /* Update global booleans for the variable's predicates. */
            evaluatePredicateeggp_dc_fy_2(morphism);
            if(!evaluateCondition())
            {
               /* Reset the boolean variables in the predicates of this variable. */
               eggp_dc_fy_b2 = true;
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
         /* All items matched! */
            return true;
      }
      else removeAssignments(morphism, new_assignments);
   }
   return false;
}

void applyeggp_dc_fy_mutateNode(Morphism *morphism, bool record_changes)
{
   Assignment var_0 = getAssignment(morphism, 0);
   string var_2 = getStringValue(morphism, 2);
   int var_3 = getIntegerValue(morphism, 3);
   int node_index = lookupNode(morphism, 0);
   int outdegree0 = getOutdegree(eggp_dc_fy_host, node_index);
   int host_node_index = lookupNode(morphism, 0);
   HostLabel label_n0 = getNodeLabel(eggp_dc_fy_host, host_node_index);
   HostLabel label;
   int list_var_length0 = 0;
   list_var_length0 += getAssignmentLength(var_0);
   int list_length0 = list_var_length0 + 1;
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
      relabelNode(eggp_dc_fy_host, host_node_index, label);
   }
   int node_array_size2 = eggp_dc_fy_host->nodes.size;
   int list_var_length1 = 0;
   int list_length1 = list_var_length1 + 2;
   HostAtom array1[list_length1];
   int index1 = 0;

   array1[index1].type = 's';
   array1[index1++].str = "Arity";
   array1[index1].type = 'i';
   array1[index1++].num = outdegree0;
   if(list_length1 > 0)
   {
      HostList *list1 = makeHostList(array1, list_length1, false);
      label = makeHostLabel(0, list_length1, list1);
   }
   else label = makeEmptyLabel(0);

   host_node_index = addNode(eggp_dc_fy_host, 1, label);
   /* If the node array size has not increased after the node addition, then
      the node was added to a hole in the array. */
   if(record_changes)
      pushAddedNode(host_node_index, node_array_size2 == eggp_dc_fy_host->nodes.size);
   int node_array_size3 = eggp_dc_fy_host->nodes.size;
   int list_var_length2 = 0;
   int list_length2 = list_var_length2 + 2;
   HostAtom array2[list_length2];
   int index2 = 0;

   array2[index2].type = 's';
   array2[index2++].str = "TArity";
   array2[index2].type = 'i';
   array2[index2++].num = var_3;
   if(list_length2 > 0)
   {
      HostList *list2 = makeHostList(array2, list_length2, false);
      label = makeHostLabel(0, list_length2, list2);
   }
   else label = makeEmptyLabel(0);

   host_node_index = addNode(eggp_dc_fy_host, 1, label);
   /* If the node array size has not increased after the node addition, then
      the node was added to a hole in the array. */
   if(record_changes)
      pushAddedNode(host_node_index, node_array_size3 == eggp_dc_fy_host->nodes.size);
   /* Reset the morphism. */
   initialiseMorphism(morphism, eggp_dc_fy_host);
}

static bool fillpot_n1(MorphismPot *pot, Morphism *morphism);
static bool fillpot_n0(MorphismPot *pot, Morphism *morphism);

bool fillpoteggp_dc_fy_mutateNode(MorphismPot *pot, Morphism *morphism)
{
   if(2 > eggp_dc_fy_host->number_of_nodes || 0 > eggp_dc_fy_host->number_of_edges) return false;
   int oldPotsize = potSize(pot);
   morphism->weight = 1.000000;
   fillpot_n1(pot, morphism);
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

static bool fillpot_n1(MorphismPot *pot, Morphism *morphism)
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
         if(label.length != 3) break;
         HostListItem *item = label.list->first;
         /* Matching rule atom 1. */
         if(item->atom.type != 's') break;
         else if(strcmp(item->atom.str, "FunctionSet") != 0) break;
         item = item->next;

         /* Matching rule atom 2. */
         int result = -1;
         /* Matching string variable 2. */
         if(item->atom.type != 's') break;
         result = addStringAssignment(morphism, 2, item->atom.str);
         if(result >= 0)
         {
            new_assignments += result;
            /* Update global booleans for the variable's predicates. */
            evaluatePredicateeggp_dc_fy_2(morphism);
            if(!evaluateCondition())
            {
               /* Reset the boolean variables in the predicates of this variable. */
               eggp_dc_fy_b2 = true;
               break;
            }
         }
         else break;
         item = item->next;

         /* Matching rule atom 3. */
         /* Matching integer variable 3. */
         if(item->atom.type != 'i') break;
         result = addIntegerAssignment(morphism, 3, item->atom.num);
         if(result >= 0)
         {
            new_assignments += result;
         }
         else break;
         match = true;
      } while(false);

      if(match)
      {
         addNodeMap(morphism, 1, host_node->index, new_assignments);
         host_node->matched = true;
         if(fillpot_n0(pot, morphism)) return true;
         else
         {
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
   for(host_index = 0; host_index < eggp_dc_fy_host->nodes.size; host_index++)
   {
      Node *host_node = getNode(eggp_dc_fy_host, host_index);
      if(host_node == NULL || host_node->index == -1) continue;
      if(host_node->matched) continue;
      if(host_node->label.mark != 3) continue;
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
         /* Matching string variable 1. */
         if(item->atom.type != 's') break;
         result = addStringAssignment(morphism, 1, item->atom.str);
         if(result >= 0)
         {
            new_assignments += result;
            /* Update global booleans for the variable's predicates. */
            evaluatePredicateeggp_dc_fy_2(morphism);
            if(!evaluateCondition())
            {
               /* Reset the boolean variables in the predicates of this variable. */
               eggp_dc_fy_b2 = true;
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
         /* All items matched! */
            putMorphism(pot, morphism, "eggp_dc_fy_mutateNode", eggp_dc_fy_host);
            removeNodeMap(morphism, 0);
            host_node->matched = false;
      }
      else removeAssignments(morphism, new_assignments);
   }
   return false;
}


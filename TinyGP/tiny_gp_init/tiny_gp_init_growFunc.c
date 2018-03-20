#include "tiny_gp_init_growFunc.h"

#include "tiny_gp_init.h"

bool tiny_gp_init_b0 = true;
bool tiny_gp_init_b1 = true;

static bool evaluateCondition(void)
{
   return (tiny_gp_init_b0 && tiny_gp_init_b1);
}

static void evaluatePredicatetiny_gp_init_0(Morphism *morphism)
{
   Assignment assignment_5 = getAssignment(morphism, 5);
   /* If the variable is not yet assigned, return. */
   if(assignment_5.type == 'n') return;
   int var_5 = getIntegerValue(morphism, 5);

   if(var_5 > 0) tiny_gp_init_b0 = true;
   else tiny_gp_init_b0 = false;
}

static void evaluatePredicatetiny_gp_init_1(Morphism *morphism)
{
   Assignment assignment_2 = getAssignment(morphism, 2);
   /* If the variable is not yet assigned, return. */
   if(assignment_2.type == 'n') return;
   int var_2 = getIntegerValue(morphism, 2);

   Assignment assignment_3 = getAssignment(morphism, 3);
   /* If the variable is not yet assigned, return. */
   if(assignment_3.type == 'n') return;
   int var_3 = getIntegerValue(morphism, 3);

   if(var_2 < var_3 - 1) tiny_gp_init_b1 = true;
   else tiny_gp_init_b1 = false;
}

static bool match_n0(Morphism *morphism);
static bool match_e0(Morphism *morphism);
static bool match_n1(Morphism *morphism);
static bool match_n2(Morphism *morphism);

bool matchtiny_gp_init_growFunc(Morphism *morphism)
{
   if(3 > tiny_gp_init_host->number_of_nodes || 1 > tiny_gp_init_host->number_of_edges) return false;
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
      do
      {
         /* The rule list does not contain a list variable, so there is no
          * match if the host list has a different length. */
         if(label.length != 2) break;
         HostListItem *item = label.list->first;
         /* Matching rule atom 1. */
         int result = -1;
         /* Matching integer variable 2. */
         if(item->atom.type != 'i') break;
         result = addIntegerAssignment(morphism, 2, item->atom.num);
         if(result >= 0)
         {
            new_assignments += result;
            /* Update global booleans for the variable's predicates. */
            evaluatePredicatetiny_gp_init_1(morphism);
            if(!evaluateCondition())
            {
               /* Reset the boolean variables in the predicates of this variable. */
               tiny_gp_init_b1 = true;
               break;
            }
         }
         else break;
         item = item->next;

         /* Matching rule atom 2. */
         /* Matching string variable 0. */
         if(item->atom.type != 's') break;
         result = addStringAssignment(morphism, 0, item->atom.str);
         if(result >= 0)
         {
            new_assignments += result;
         }
         else break;
         match = true;
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
         /* Matching integer variable 5. */
         if(item->atom.type != 'i') break;
         result = addIntegerAssignment(morphism, 5, item->atom.num);
         if(result >= 0)
         {
            new_assignments += result;
            /* Update global booleans for the variable's predicates. */
            evaluatePredicatetiny_gp_init_0(morphism);
            if(!evaluateCondition())
            {
               /* Reset the boolean variables in the predicates of this variable. */
               tiny_gp_init_b0 = true;
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
         if(match_n1(morphism)) return true;
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

static bool match_n1(Morphism *morphism)
{
   RootNodes *nodes;
   for(nodes = getRootNodeList(tiny_gp_init_host); nodes != NULL; nodes = nodes->next)
   {
      Node *host_node = getNode(tiny_gp_init_host, nodes->index);
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
         /* Matching string variable 1. */
         if(item->atom.type != 's') break;
         result = addStringAssignment(morphism, 1, item->atom.str);
         if(result >= 0)
         {
            new_assignments += result;
         }
         else break;
         item = item->next;

         /* Matching rule atom 3. */
         /* Matching integer variable 4. */
         if(item->atom.type != 'i') break;
         result = addIntegerAssignment(morphism, 4, item->atom.num);
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
         if(match_n2(morphism)) return true;
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

static bool match_n2(Morphism *morphism)
{
   RootNodes *nodes;
   for(nodes = getRootNodeList(tiny_gp_init_host); nodes != NULL; nodes = nodes->next)
   {
      Node *host_node = getNode(tiny_gp_init_host, nodes->index);
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
         /* Matching integer variable 3. */
         if(item->atom.type != 'i') break;
         result = addIntegerAssignment(morphism, 3, item->atom.num);
         if(result >= 0)
         {
            new_assignments += result;
            /* Update global booleans for the variable's predicates. */
            evaluatePredicatetiny_gp_init_1(morphism);
            if(!evaluateCondition())
            {
               /* Reset the boolean variables in the predicates of this variable. */
               tiny_gp_init_b1 = true;
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
         /* All items matched! */
            return true;
      }
      else removeAssignments(morphism, new_assignments);
   }
   return false;
}

void applytiny_gp_init_growFunc(Morphism *morphism, bool record_changes)
{
   string var_1 = getStringValue(morphism, 1);
   int var_2 = getIntegerValue(morphism, 2);
   int var_4 = getIntegerValue(morphism, 4);
   int var_5 = getIntegerValue(morphism, 5);
   int host_edge_index = lookupEdge(morphism, 0);
   HostLabel label_e0 = getEdgeLabel(tiny_gp_init_host, host_edge_index);
   HostLabel label;
   int list_var_length0 = 0;
   int list_length0 = list_var_length0 + 1;
   HostAtom array0[list_length0];
   int index0 = 0;

   array0[index0].type = 'i';
   array0[index0++].num = var_5 - 1;
   if(list_length0 > 0)
   {
      HostList *list0 = makeHostList(array0, list_length0, false);
      label = makeHostLabel(0, list_length0, list0);
   }
   else label = makeEmptyLabel(0);

   /* Relabel the edge if its label is not equal to the RHS label. */
   if(equalHostLabels(label_e0, label)) removeHostList(label.list);
   else
   {
      if(record_changes) pushRelabelledEdge(host_edge_index, label_e0);
      relabelEdge(tiny_gp_init_host, host_edge_index, label);
   }
   /* Array of host node indices indexed by RHS node index. */
   int rhs_node_map[4];

   int host_node_index;
   int node_array_size3 = tiny_gp_init_host->nodes.size;
   int list_var_length1 = 0;
   int list_length1 = list_var_length1 + 2;
   HostAtom array1[list_length1];
   int index1 = 0;

   array1[index1].type = 'i';
   array1[index1++].num = var_2 + 1;
   array1[index1].type = 's';
   array1[index1++].str = var_1;
   if(list_length1 > 0)
   {
      HostList *list1 = makeHostList(array1, list_length1, false);
      label = makeHostLabel(0, list_length1, list1);
   }
   else label = makeEmptyLabel(0);

   host_node_index = addNode(tiny_gp_init_host, 1, label);
   rhs_node_map[3] = host_node_index;
   /* If the node array size has not increased after the node addition, then
      the node was added to a hole in the array. */
   if(record_changes)
      pushAddedNode(host_node_index, node_array_size3 == tiny_gp_init_host->nodes.size);
   int source, target;
   int edge_array_size1 = tiny_gp_init_host->edges.size;
   source = lookupNode(morphism, 0);
   target = rhs_node_map[3];
   int list_var_length2 = 0;
   int list_length2 = list_var_length2 + 1;
   HostAtom array2[list_length2];
   int index2 = 0;

   array2[index2].type = 'i';
   array2[index2++].num = var_5 - 1;
   if(list_length2 > 0)
   {
      HostList *list2 = makeHostList(array2, list_length2, false);
      label = makeHostLabel(0, list_length2, list2);
   }
   else label = makeEmptyLabel(0);

   host_edge_index = addEdge(tiny_gp_init_host, label, source, target);
   /* If the edge array size has not increased after the edge addition, then
      the edge was added to a hole in the array. */
   if(record_changes)
      pushAddedEdge(host_edge_index, edge_array_size1 == tiny_gp_init_host->edges.size);
   int edge_array_size2 = tiny_gp_init_host->edges.size;
   source = rhs_node_map[3];
   target = rhs_node_map[3];
   int list_var_length3 = 0;
   int list_length3 = list_var_length3 + 1;
   HostAtom array3[list_length3];
   int index3 = 0;

   array3[index3].type = 'i';
   array3[index3++].num = var_4;
   if(list_length3 > 0)
   {
      HostList *list3 = makeHostList(array3, list_length3, false);
      label = makeHostLabel(0, list_length3, list3);
   }
   else label = makeEmptyLabel(0);

   host_edge_index = addEdge(tiny_gp_init_host, label, source, target);
   /* If the edge array size has not increased after the edge addition, then
      the edge was added to a hole in the array. */
   if(record_changes)
      pushAddedEdge(host_edge_index, edge_array_size2 == tiny_gp_init_host->edges.size);
   /* Reset the morphism. */
   initialiseMorphism(morphism, tiny_gp_init_host);
}

static bool fillpot_n0(MorphismPot *pot, Morphism *morphism);
static bool fillpot_e0(MorphismPot *pot, Morphism *morphism);
static bool fillpot_n1(MorphismPot *pot, Morphism *morphism);
static bool fillpot_n2(MorphismPot *pot, Morphism *morphism);

bool fillpottiny_gp_init_growFunc(MorphismPot *pot, Morphism *morphism)
{
   if(3 > tiny_gp_init_host->number_of_nodes || 1 > tiny_gp_init_host->number_of_edges) return false;
   int oldPotsize = potSize(pot);
   morphism->weight = 1.000000;
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
      do
      {
         /* The rule list does not contain a list variable, so there is no
          * match if the host list has a different length. */
         if(label.length != 2) break;
         HostListItem *item = label.list->first;
         /* Matching rule atom 1. */
         int result = -1;
         /* Matching integer variable 2. */
         if(item->atom.type != 'i') break;
         result = addIntegerAssignment(morphism, 2, item->atom.num);
         if(result >= 0)
         {
            new_assignments += result;
            /* Update global booleans for the variable's predicates. */
            evaluatePredicatetiny_gp_init_1(morphism);
            if(!evaluateCondition())
            {
               /* Reset the boolean variables in the predicates of this variable. */
               tiny_gp_init_b1 = true;
               break;
            }
         }
         else break;
         item = item->next;

         /* Matching rule atom 2. */
         /* Matching string variable 0. */
         if(item->atom.type != 's') break;
         result = addStringAssignment(morphism, 0, item->atom.str);
         if(result >= 0)
         {
            new_assignments += result;
         }
         else break;
         match = true;
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
         /* Matching integer variable 5. */
         if(item->atom.type != 'i') break;
         result = addIntegerAssignment(morphism, 5, item->atom.num);
         if(result >= 0)
         {
            new_assignments += result;
            /* Update global booleans for the variable's predicates. */
            evaluatePredicatetiny_gp_init_0(morphism);
            if(!evaluateCondition())
            {
               /* Reset the boolean variables in the predicates of this variable. */
               tiny_gp_init_b0 = true;
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
         if(fillpot_n1(pot, morphism)) return true;
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

static bool fillpot_n1(MorphismPot *pot, Morphism *morphism)
{
   RootNodes *nodes;
   for(nodes = getRootNodeList(tiny_gp_init_host); nodes != NULL; nodes = nodes->next)
   {
      Node *host_node = getNode(tiny_gp_init_host, nodes->index);
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
         /* Matching string variable 1. */
         if(item->atom.type != 's') break;
         result = addStringAssignment(morphism, 1, item->atom.str);
         if(result >= 0)
         {
            new_assignments += result;
         }
         else break;
         item = item->next;

         /* Matching rule atom 3. */
         /* Matching integer variable 4. */
         if(item->atom.type != 'i') break;
         result = addIntegerAssignment(morphism, 4, item->atom.num);
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
         if(fillpot_n2(pot, morphism)) return true;
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

static bool fillpot_n2(MorphismPot *pot, Morphism *morphism)
{
   RootNodes *nodes;
   for(nodes = getRootNodeList(tiny_gp_init_host); nodes != NULL; nodes = nodes->next)
   {
      Node *host_node = getNode(tiny_gp_init_host, nodes->index);
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
         /* Matching integer variable 3. */
         if(item->atom.type != 'i') break;
         result = addIntegerAssignment(morphism, 3, item->atom.num);
         if(result >= 0)
         {
            new_assignments += result;
            /* Update global booleans for the variable's predicates. */
            evaluatePredicatetiny_gp_init_1(morphism);
            if(!evaluateCondition())
            {
               /* Reset the boolean variables in the predicates of this variable. */
               tiny_gp_init_b1 = true;
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
         /* All items matched! */
            putMorphism(pot, morphism, "tiny_gp_init_growFunc", tiny_gp_init_host);
            removeNodeMap(morphism, 2);
            host_node->matched = false;
      }
      else removeAssignments(morphism, new_assignments);
   }
   return false;
}


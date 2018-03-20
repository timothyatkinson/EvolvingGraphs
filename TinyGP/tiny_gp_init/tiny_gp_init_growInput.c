#include "tiny_gp_init_growInput.h"

#include "tiny_gp_init.h"

bool tiny_gp_init_b2 = true;
bool tiny_gp_init_b3 = true;

static bool evaluateCondition(void)
{
   return (tiny_gp_init_b2 && tiny_gp_init_b3);
}

static void evaluatePredicatetiny_gp_init_2(Morphism *morphism)
{
   Assignment assignment_4 = getAssignment(morphism, 4);
   /* If the variable is not yet assigned, return. */
   if(assignment_4.type == 'n') return;
   int var_4 = getIntegerValue(morphism, 4);

   if(var_4 > 0) tiny_gp_init_b2 = true;
   else tiny_gp_init_b2 = false;
}

static void evaluatePredicatetiny_gp_init_3(Morphism *morphism)
{
   Assignment assignment_1 = getAssignment(morphism, 1);
   /* If the variable is not yet assigned, return. */
   if(assignment_1.type == 'n') return;
   int var_1 = getIntegerValue(morphism, 1);

   Assignment assignment_2 = getAssignment(morphism, 2);
   /* If the variable is not yet assigned, return. */
   if(assignment_2.type == 'n') return;
   int var_2 = getIntegerValue(morphism, 2);

   if(var_1 == var_2 - 1) tiny_gp_init_b3 = true;
   else tiny_gp_init_b3 = false;
}

static bool match_n0(Morphism *morphism);
static bool match_e0(Morphism *morphism);
static bool match_n2(Morphism *morphism);
static bool match_n1(Morphism *morphism);

bool matchtiny_gp_init_growInput(Morphism *morphism)
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
         /* Matching integer variable 1. */
         if(item->atom.type != 'i') break;
         result = addIntegerAssignment(morphism, 1, item->atom.num);
         if(result >= 0)
         {
            new_assignments += result;
            /* Update global booleans for the variable's predicates. */
            evaluatePredicatetiny_gp_init_3(morphism);
            if(!evaluateCondition())
            {
               /* Reset the boolean variables in the predicates of this variable. */
               tiny_gp_init_b3 = true;
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
         /* Matching integer variable 4. */
         if(item->atom.type != 'i') break;
         result = addIntegerAssignment(morphism, 4, item->atom.num);
         if(result >= 0)
         {
            new_assignments += result;
            /* Update global booleans for the variable's predicates. */
            evaluatePredicatetiny_gp_init_2(morphism);
            if(!evaluateCondition())
            {
               /* Reset the boolean variables in the predicates of this variable. */
               tiny_gp_init_b2 = true;
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
         if(match_n2(morphism)) return true;
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
         /* Matching integer variable 2. */
         if(item->atom.type != 'i') break;
         result = addIntegerAssignment(morphism, 2, item->atom.num);
         if(result >= 0)
         {
            new_assignments += result;
            /* Update global booleans for the variable's predicates. */
            evaluatePredicatetiny_gp_init_3(morphism);
            if(!evaluateCondition())
            {
               /* Reset the boolean variables in the predicates of this variable. */
               tiny_gp_init_b3 = true;
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
         if(match_n1(morphism)) return true;
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

static bool match_n1(Morphism *morphism)
{
   int host_index;
   for(host_index = 0; host_index < tiny_gp_init_host->nodes.size; host_index++)
   {
      Node *host_node = getNode(tiny_gp_init_host, host_index);
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
         /* The rule list does not contain a list variable, so there is no
          * match if the host list has a different length. */
         if(label.length != 2) break;
         HostListItem *item = label.list->first;
         /* Matching rule atom 1. */
         int result = -1;
         /* Matching integer variable 3. */
         if(item->atom.type != 'i') break;
         result = addIntegerAssignment(morphism, 3, item->atom.num);
         if(result >= 0)
         {
            new_assignments += result;
         }
         else break;
         item = item->next;

         /* Matching rule atom 2. */
         if(item->atom.type != 's') break;
         else if(strcmp(item->atom.str, "IN") != 0) break;
         match = true;
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

void applytiny_gp_init_growInput(Morphism *morphism, bool record_changes)
{
   int var_4 = getIntegerValue(morphism, 4);
   int host_edge_index = lookupEdge(morphism, 0);
   HostLabel label_e0 = getEdgeLabel(tiny_gp_init_host, host_edge_index);
   HostLabel label;
   int list_var_length0 = 0;
   int list_length0 = list_var_length0 + 1;
   HostAtom array0[list_length0];
   int index0 = 0;

   array0[index0].type = 'i';
   array0[index0++].num = var_4 - 1;
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
   int source, target;
   int edge_array_size1 = tiny_gp_init_host->edges.size;
   source = lookupNode(morphism, 0);
   target = lookupNode(morphism, 1);
   int list_var_length1 = 0;
   int list_length1 = list_var_length1 + 1;
   HostAtom array1[list_length1];
   int index1 = 0;

   array1[index1].type = 'i';
   array1[index1++].num = var_4 - 1;
   if(list_length1 > 0)
   {
      HostList *list1 = makeHostList(array1, list_length1, false);
      label = makeHostLabel(0, list_length1, list1);
   }
   else label = makeEmptyLabel(0);

   host_edge_index = addEdge(tiny_gp_init_host, label, source, target);
   /* If the edge array size has not increased after the edge addition, then
      the edge was added to a hole in the array. */
   if(record_changes)
      pushAddedEdge(host_edge_index, edge_array_size1 == tiny_gp_init_host->edges.size);
   /* Reset the morphism. */
   initialiseMorphism(morphism, tiny_gp_init_host);
}

static bool fillpot_n0(MorphismPot *pot, Morphism *morphism);
static bool fillpot_e0(MorphismPot *pot, Morphism *morphism);
static bool fillpot_n2(MorphismPot *pot, Morphism *morphism);
static bool fillpot_n1(MorphismPot *pot, Morphism *morphism);

bool fillpottiny_gp_init_growInput(MorphismPot *pot, Morphism *morphism)
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
         /* Matching integer variable 1. */
         if(item->atom.type != 'i') break;
         result = addIntegerAssignment(morphism, 1, item->atom.num);
         if(result >= 0)
         {
            new_assignments += result;
            /* Update global booleans for the variable's predicates. */
            evaluatePredicatetiny_gp_init_3(morphism);
            if(!evaluateCondition())
            {
               /* Reset the boolean variables in the predicates of this variable. */
               tiny_gp_init_b3 = true;
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
         /* Matching integer variable 4. */
         if(item->atom.type != 'i') break;
         result = addIntegerAssignment(morphism, 4, item->atom.num);
         if(result >= 0)
         {
            new_assignments += result;
            /* Update global booleans for the variable's predicates. */
            evaluatePredicatetiny_gp_init_2(morphism);
            if(!evaluateCondition())
            {
               /* Reset the boolean variables in the predicates of this variable. */
               tiny_gp_init_b2 = true;
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
         if(fillpot_n2(pot, morphism)) return true;
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
         /* Matching integer variable 2. */
         if(item->atom.type != 'i') break;
         result = addIntegerAssignment(morphism, 2, item->atom.num);
         if(result >= 0)
         {
            new_assignments += result;
            /* Update global booleans for the variable's predicates. */
            evaluatePredicatetiny_gp_init_3(morphism);
            if(!evaluateCondition())
            {
               /* Reset the boolean variables in the predicates of this variable. */
               tiny_gp_init_b3 = true;
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
         if(fillpot_n1(pot, morphism)) return true;
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

static bool fillpot_n1(MorphismPot *pot, Morphism *morphism)
{
   int host_index;
   for(host_index = 0; host_index < tiny_gp_init_host->nodes.size; host_index++)
   {
      Node *host_node = getNode(tiny_gp_init_host, host_index);
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
         /* The rule list does not contain a list variable, so there is no
          * match if the host list has a different length. */
         if(label.length != 2) break;
         HostListItem *item = label.list->first;
         /* Matching rule atom 1. */
         int result = -1;
         /* Matching integer variable 3. */
         if(item->atom.type != 'i') break;
         result = addIntegerAssignment(morphism, 3, item->atom.num);
         if(result >= 0)
         {
            new_assignments += result;
         }
         else break;
         item = item->next;

         /* Matching rule atom 2. */
         if(item->atom.type != 's') break;
         else if(strcmp(item->atom.str, "IN") != 0) break;
         match = true;
      } while(false);

      if(match)
      {
         addNodeMap(morphism, 1, host_node->index, new_assignments);
         host_node->matched = true;
         /* All items matched! */
            putMorphism(pot, morphism, "tiny_gp_init_growInput", tiny_gp_init_host);
            removeNodeMap(morphism, 1);
            host_node->matched = false;
      }
      else removeAssignments(morphism, new_assignments);
   }
   return false;
}


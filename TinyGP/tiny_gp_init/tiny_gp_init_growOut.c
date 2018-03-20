#include "tiny_gp_init_growOut.h"

#include "tiny_gp_init.h"

static bool match_n0(Morphism *morphism);
static bool match_n1(Morphism *morphism);

bool matchtiny_gp_init_growOut(Morphism *morphism)
{
   if(2 > tiny_gp_init_host->number_of_nodes || 0 > tiny_gp_init_host->number_of_edges) return false;
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
      if(host_node->indegree < 0 || host_node->outdegree < 0 ||
         ((host_node->outdegree + host_node->indegree - 0 - 0 - 0) < 0)) continue;

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
         if(item->atom.type != 's') break;
         else if(strcmp(item->atom.str, "OUT") != 0) break;
         item = item->prev;
         /* Check if the host list has passed "start". */
         if(item == start->prev) break;
         /* Matching rule atom 2 */
         /* Matching integer variable 2. */
         if(item->atom.type != 'i') break;
         result = addIntegerAssignment(morphism, 2, item->atom.num);
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
         /* All items matched! */
            return true;
      }
      else removeAssignments(morphism, new_assignments);
   }
   return false;
}

void applytiny_gp_init_growOut(Morphism *morphism, bool record_changes)
{
   string var_1 = getStringValue(morphism, 1);
   int var_2 = getIntegerValue(morphism, 2);
   int var_3 = getIntegerValue(morphism, 3);
   int host_node_index = lookupNode(morphism, 0);
   if(record_changes) pushChangedRootNode(host_node_index);
   changeRoot(tiny_gp_init_host, host_node_index);
   /* Array of host node indices indexed by RHS node index. */
   int rhs_node_map[3];

   int node_array_size2 = tiny_gp_init_host->nodes.size;
   HostLabel label;
   int list_var_length0 = 0;
   int list_length0 = list_var_length0 + 2;
   HostAtom array0[list_length0];
   int index0 = 0;

   array0[index0].type = 'i';
   array0[index0++].num = var_2 + 1;
   array0[index0].type = 's';
   array0[index0++].str = var_1;
   if(list_length0 > 0)
   {
      HostList *list0 = makeHostList(array0, list_length0, false);
      label = makeHostLabel(0, list_length0, list0);
   }
   else label = makeEmptyLabel(0);

   host_node_index = addNode(tiny_gp_init_host, 1, label);
   rhs_node_map[2] = host_node_index;
   /* If the node array size has not increased after the node addition, then
      the node was added to a hole in the array. */
   if(record_changes)
      pushAddedNode(host_node_index, node_array_size2 == tiny_gp_init_host->nodes.size);
   int host_edge_index;
   int source, target;
   int edge_array_size0 = tiny_gp_init_host->edges.size;
   source = lookupNode(morphism, 0);
   target = rhs_node_map[2];
   int list_var_length1 = 0;
   int list_length1 = list_var_length1 + 1;
   HostAtom array1[list_length1];
   int index1 = 0;

   array1[index1].type = 'i';
   array1[index1++].num = 0;
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
      pushAddedEdge(host_edge_index, edge_array_size0 == tiny_gp_init_host->edges.size);
   int edge_array_size1 = tiny_gp_init_host->edges.size;
   source = rhs_node_map[2];
   target = rhs_node_map[2];
   int list_var_length2 = 0;
   int list_length2 = list_var_length2 + 1;
   HostAtom array2[list_length2];
   int index2 = 0;

   array2[index2].type = 'i';
   array2[index2++].num = var_3;
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
   /* Reset the morphism. */
   initialiseMorphism(morphism, tiny_gp_init_host);
}

static bool fillpot_n0(MorphismPot *pot, Morphism *morphism);
static bool fillpot_n1(MorphismPot *pot, Morphism *morphism);

bool fillpottiny_gp_init_growOut(MorphismPot *pot, Morphism *morphism)
{
   if(2 > tiny_gp_init_host->number_of_nodes || 0 > tiny_gp_init_host->number_of_edges) return false;
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
      if(host_node->indegree < 0 || host_node->outdegree < 0 ||
         ((host_node->outdegree + host_node->indegree - 0 - 0 - 0) < 0)) continue;

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
         if(item->atom.type != 's') break;
         else if(strcmp(item->atom.str, "OUT") != 0) break;
         item = item->prev;
         /* Check if the host list has passed "start". */
         if(item == start->prev) break;
         /* Matching rule atom 2 */
         /* Matching integer variable 2. */
         if(item->atom.type != 'i') break;
         result = addIntegerAssignment(morphism, 2, item->atom.num);
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
         /* All items matched! */
            putMorphism(pot, morphism, "tiny_gp_init_growOut", tiny_gp_init_host);
            removeNodeMap(morphism, 1);
            host_node->matched = false;
      }
      else removeAssignments(morphism, new_assignments);
   }
   return false;
}


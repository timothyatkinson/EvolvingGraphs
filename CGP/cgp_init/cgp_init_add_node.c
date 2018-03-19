#include "cgp_init_add_node.h"

#include "cgp_init.h"

static bool match_n0(Morphism *morphism);
static bool match_n1(Morphism *morphism);
static bool match_n2(Morphism *morphism);

bool matchcgp_init_add_node(Morphism *morphism)
{
   if(3 > cgp_init_host->number_of_nodes || 0 > cgp_init_host->number_of_edges) return false;
   if(match_n0(morphism)) return true;
   else
   {
      initialiseMorphism(morphism, cgp_init_host);
      return false;
   }
}

static bool match_n0(Morphism *morphism)
{
   RootNodes *nodes;
   for(nodes = getRootNodeList(cgp_init_host); nodes != NULL; nodes = nodes->next)
   {
      Node *host_node = getNode(cgp_init_host, nodes->index);
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
         else if(strcmp(item->atom.str, "NodesAdded") != 0) break;
         item = item->next;

         /* Matching rule atom 2. */
         int result = -1;
         /* Matching integer variable 0. */
         if(item->atom.type != 'i') break;
         result = addIntegerAssignment(morphism, 0, item->atom.num);
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
   for(nodes = getRootNodeList(cgp_init_host); nodes != NULL; nodes = nodes->next)
   {
      Node *host_node = getNode(cgp_init_host, nodes->index);
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
         /* Matching string variable 3. */
         if(item->atom.type != 's') break;
         result = addStringAssignment(morphism, 3, item->atom.str);
         if(result >= 0)
         {
            new_assignments += result;
         }
         else break;
         item = item->next;

         /* Matching rule atom 3. */
         /* Matching integer variable 1. */
         if(item->atom.type != 'i') break;
         result = addIntegerAssignment(morphism, 1, item->atom.num);
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
   for(nodes = getRootNodeList(cgp_init_host); nodes != NULL; nodes = nodes->next)
   {
      Node *host_node = getNode(cgp_init_host, nodes->index);
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
         else if(strcmp(item->atom.str, "Inputs") != 0) break;
         item = item->next;

         /* Matching rule atom 2. */
         int result = -1;
         /* Matching integer variable 2. */
         if(item->atom.type != 'i') break;
         result = addIntegerAssignment(morphism, 2, item->atom.num);
         if(result >= 0)
         {
            new_assignments += result;
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

void applycgp_init_add_node(Morphism *morphism, bool record_changes)
{
   int var_0 = getIntegerValue(morphism, 0);
   int var_2 = getIntegerValue(morphism, 2);
   string var_3 = getStringValue(morphism, 3);
   int host_node_index = lookupNode(morphism, 0);
   HostLabel label_n0 = getNodeLabel(cgp_init_host, host_node_index);
   HostLabel label;
   int list_var_length0 = 0;
   int list_length0 = list_var_length0 + 2;
   HostAtom array0[list_length0];
   int index0 = 0;

   array0[index0].type = 's';
   array0[index0++].str = "NodesAdded";
   array0[index0].type = 'i';
   array0[index0++].num = var_0 + 1;
   if(list_length0 > 0)
   {
      HostList *list0 = makeHostList(array0, list_length0, false);
      label = makeHostLabel(0, list_length0, list0);
   }
   else label = makeEmptyLabel(0);

   if(equalHostLabels(label_n0, label)) removeHostList(label.list);
   else
   {
      if(record_changes) pushRelabelledNode(host_node_index, label_n0);
      relabelNode(cgp_init_host, host_node_index, label);
   }
   int node_array_size2 = cgp_init_host->nodes.size;
   int list_var_length1 = 0;
   int list_length1 = list_var_length1 + 2;
   HostAtom array1[list_length1];
   int index1 = 0;

   array1[index1].type = 'i';
   array1[index1++].num = var_0 + var_2;
   array1[index1].type = 's';
   array1[index1++].str = var_3;
   if(list_length1 > 0)
   {
      HostList *list1 = makeHostList(array1, list_length1, false);
      label = makeHostLabel(3, list_length1, list1);
   }
   else label = makeEmptyLabel(3);

   host_node_index = addNode(cgp_init_host, 1, label);
   /* If the node array size has not increased after the node addition, then
      the node was added to a hole in the array. */
   if(record_changes)
      pushAddedNode(host_node_index, node_array_size2 == cgp_init_host->nodes.size);
   /* Reset the morphism. */
   initialiseMorphism(morphism, cgp_init_host);
}

static bool fillpot_n0(MorphismPot *pot, Morphism *morphism);
static bool fillpot_n1(MorphismPot *pot, Morphism *morphism);
static bool fillpot_n2(MorphismPot *pot, Morphism *morphism);

bool fillpotcgp_init_add_node(MorphismPot *pot, Morphism *morphism)
{
   if(3 > cgp_init_host->number_of_nodes || 0 > cgp_init_host->number_of_edges) return false;
   int oldPotsize = potSize(pot);
   morphism->weight = 1.000000;
   fillpot_n0(pot, morphism);
   if(potSize(pot) > oldPotsize){
      initialiseMorphism(morphism, cgp_init_host);
      return true;
   }
   else
   {
      initialiseMorphism(morphism, cgp_init_host);
      return false;
   }
}

static bool fillpot_n0(MorphismPot *pot, Morphism *morphism)
{
   RootNodes *nodes;
   for(nodes = getRootNodeList(cgp_init_host); nodes != NULL; nodes = nodes->next)
   {
      Node *host_node = getNode(cgp_init_host, nodes->index);
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
         else if(strcmp(item->atom.str, "NodesAdded") != 0) break;
         item = item->next;

         /* Matching rule atom 2. */
         int result = -1;
         /* Matching integer variable 0. */
         if(item->atom.type != 'i') break;
         result = addIntegerAssignment(morphism, 0, item->atom.num);
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
   for(nodes = getRootNodeList(cgp_init_host); nodes != NULL; nodes = nodes->next)
   {
      Node *host_node = getNode(cgp_init_host, nodes->index);
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
         /* Matching string variable 3. */
         if(item->atom.type != 's') break;
         result = addStringAssignment(morphism, 3, item->atom.str);
         if(result >= 0)
         {
            new_assignments += result;
         }
         else break;
         item = item->next;

         /* Matching rule atom 3. */
         /* Matching integer variable 1. */
         if(item->atom.type != 'i') break;
         result = addIntegerAssignment(morphism, 1, item->atom.num);
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
   for(nodes = getRootNodeList(cgp_init_host); nodes != NULL; nodes = nodes->next)
   {
      Node *host_node = getNode(cgp_init_host, nodes->index);
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
         else if(strcmp(item->atom.str, "Inputs") != 0) break;
         item = item->next;

         /* Matching rule atom 2. */
         int result = -1;
         /* Matching integer variable 2. */
         if(item->atom.type != 'i') break;
         result = addIntegerAssignment(morphism, 2, item->atom.num);
         if(result >= 0)
         {
            new_assignments += result;
         }
         else break;
         match = true;
      } while(false);

      if(match)
      {
         addNodeMap(morphism, 2, host_node->index, new_assignments);
         host_node->matched = true;
         /* All items matched! */
            putMorphism(pot, morphism, "cgp_init_add_node", cgp_init_host);
            removeNodeMap(morphism, 2);
            host_node->matched = false;
      }
      else removeAssignments(morphism, new_assignments);
   }
   return false;
}


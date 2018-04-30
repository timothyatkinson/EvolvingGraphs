#include "n_node_pickNode.h"

#include "n_node.h"

bool n_node_b2 = true;
bool n_node_b3 = true;
bool n_node_b4 = false;

static bool evaluateCondition(void)
{
   return ((n_node_b2 && n_node_b3) && !n_node_b4);
}

static void evaluatePredicaten_node_2(Morphism *morphism)
{
   Assignment assignment_0 = getAssignment(morphism, 0);
   /* If the variable is not yet assigned, return. */
   if(assignment_0.type == 'n') return;
   string var_0 = getStringValue(morphism, 0);

   int list_var_length0 = 0;
   int list_length0 = list_var_length0 + 1;
   HostAtom array0[list_length0];
   int index0 = 0;

   array0[index0].type = 's';
   array0[index0++].str = var_0;

   int list_var_length1 = 0;
   int list_length1 = list_var_length1 + 1;
   HostAtom array1[list_length1];
   int index1 = 0;

   array1[index1].type = 's';
   array1[index1++].str = "IN";

   if(!equalHostLists(array0, array1, list_length0, list_length1)) n_node_b2 = true;
   else n_node_b2 = false;
}

static void evaluatePredicaten_node_3(Morphism *morphism)
{
   Assignment assignment_0 = getAssignment(morphism, 0);
   /* If the variable is not yet assigned, return. */
   if(assignment_0.type == 'n') return;
   string var_0 = getStringValue(morphism, 0);

   int list_var_length0 = 0;
   int list_length0 = list_var_length0 + 1;
   HostAtom array0[list_length0];
   int index0 = 0;

   array0[index0].type = 's';
   array0[index0++].str = var_0;

   int list_var_length1 = 0;
   int list_length1 = list_var_length1 + 1;
   HostAtom array1[list_length1];
   int index1 = 0;

   array1[index1].type = 's';
   array1[index1++].str = "OUT";

   if(!equalHostLists(array0, array1, list_length0, list_length1)) n_node_b3 = true;
   else n_node_b3 = false;
}

static void evaluatePredicaten_node_4(Morphism *morphism)
{
   int n0 = lookupNode(morphism, 0);
   /* If the node is not yet matched by the morphism, return. */
   if(n0 == -1) return;

   int n1 = lookupNode(morphism, 1);
   /* If the node is not yet matched by the morphism, return. */
   if(n1 == -1) return;

   Node *source = getNode(n_node_host, n1);
   bool edge_found = false;
   int counter;
   for(counter = 0; counter < source->out_edges.size + 2; counter++)
   {
      Edge *edge = getNthOutEdge(n_node_host, source, counter);
      if(edge != NULL && edge->target == n0)
      {
         n_node_b4 = true;
         edge_found = true;
         break;
      }
   }
   if(!edge_found) n_node_b4 = false;
}

static bool match_n1(Morphism *morphism);
static bool match_n0(Morphism *morphism);

bool matchn_node_pickNode(Morphism *morphism)
{
   if(2 > n_node_host->number_of_nodes || 0 > n_node_host->number_of_edges) return false;
   if(match_n1(morphism)) return true;
   else
   {
      initialiseMorphism(morphism, n_node_host);
      return false;
   }
}

static bool match_n1(Morphism *morphism)
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
         addNodeMap(morphism, 1, host_node->index, new_assignments);
         host_node->matched = true;
         /* Update global booleans representing the node's predicates. */
         evaluatePredicaten_node_4(morphism);
         bool next_match_result = false;
         if(evaluateCondition()) next_match_result = match_n0(morphism);
         if(next_match_result) return true;
         else
         {
            /* Reset the boolean variables in the predicates of this node. */
            n_node_b4 = false;
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
   for(host_index = 0; host_index < n_node_host->nodes.size; host_index++)
   {
      Node *host_node = getNode(n_node_host, host_index);
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
         if(label.length != 1) break;
         HostListItem *item = label.list->first;
         /* Matching rule atom 1. */
         int result = -1;
         /* Matching string variable 0. */
         if(item->atom.type != 's') break;
         result = addStringAssignment(morphism, 0, item->atom.str);
         if(result >= 0)
         {
            new_assignments += result;
            /* Update global booleans for the variable's predicates. */
            evaluatePredicaten_node_2(morphism);
            evaluatePredicaten_node_3(morphism);
            if(!evaluateCondition())
            {
               /* Reset the boolean variables in the predicates of this variable. */
               n_node_b2 = true;
               n_node_b3 = true;
               break;
            }
         }
         else break;
         match = true;
      } while(false);

      if(match)
      {
         addNodeMap(morphism, 0, host_node->index, new_assignments);
         host_node->matched = true;
         /* Update global booleans representing the node's predicates. */
         evaluatePredicaten_node_4(morphism);
         if(evaluateCondition())
         {
            /* All items matched! */
            return true;
         }
         else
         {
            /* Reset the boolean variables in the predicates of this node. */
            n_node_b4 = false;
            removeNodeMap(morphism, 0);
            host_node->matched = false;
         }
      }
      else removeAssignments(morphism, new_assignments);
   }
   return false;
}

void applyn_node_pickNode(Morphism *morphism, bool record_changes)
{
   int host_node_index = lookupNode(morphism, 0);
   HostLabel label_n0 = getNodeLabel(n_node_host, host_node_index);
   if(record_changes) pushRemarkedNode(host_node_index, label_n0.mark);
   changeNodeMark(n_node_host, host_node_index, 3);

   /* Reset the morphism. */
   initialiseMorphism(morphism, n_node_host);
}

static bool fillpot_n1(MorphismPot *pot, Morphism *morphism);
static bool fillpot_n0(MorphismPot *pot, Morphism *morphism);

bool fillpotn_node_pickNode(MorphismPot *pot, Morphism *morphism)
{
   if(2 > n_node_host->number_of_nodes || 0 > n_node_host->number_of_edges) return false;
   int oldPotsize = potSize(pot);
   morphism->weight = 1.000000;
   fillpot_n1(pot, morphism);
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

static bool fillpot_n1(MorphismPot *pot, Morphism *morphism)
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
         addNodeMap(morphism, 1, host_node->index, new_assignments);
         host_node->matched = true;
         /* Update global booleans representing the node's predicates. */
         evaluatePredicaten_node_4(morphism);
         bool next_match_result = false;
         if(evaluateCondition()) next_match_result = fillpot_n0(pot, morphism);
         if(next_match_result) return true;
         else
         {
            /* Reset the boolean variables in the predicates of this node. */
            n_node_b4 = false;
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
   for(host_index = 0; host_index < n_node_host->nodes.size; host_index++)
   {
      Node *host_node = getNode(n_node_host, host_index);
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
         if(label.length != 1) break;
         HostListItem *item = label.list->first;
         /* Matching rule atom 1. */
         int result = -1;
         /* Matching string variable 0. */
         if(item->atom.type != 's') break;
         result = addStringAssignment(morphism, 0, item->atom.str);
         if(result >= 0)
         {
            new_assignments += result;
            /* Update global booleans for the variable's predicates. */
            evaluatePredicaten_node_2(morphism);
            evaluatePredicaten_node_3(morphism);
            if(!evaluateCondition())
            {
               /* Reset the boolean variables in the predicates of this variable. */
               n_node_b2 = true;
               n_node_b3 = true;
               break;
            }
         }
         else break;
         match = true;
      } while(false);

      if(match)
      {
         addNodeMap(morphism, 0, host_node->index, new_assignments);
         host_node->matched = true;
         /* Update global booleans representing the node's predicates. */
         evaluatePredicaten_node_4(morphism);
         if(evaluateCondition())
         {
            /* All items matched! */
            putMorphism(pot, morphism, "n_node_pickNode", n_node_host);
            /* Reset the boolean variables in the predicates of this node. */
            n_node_b4 = false;
            removeNodeMap(morphism, 0);
            host_node->matched = false;
            return false;
         }
         else
         {
            /* Reset the boolean variables in the predicates of this node. */
            n_node_b4 = false;
            removeNodeMap(morphism, 0);
            host_node->matched = false;
         }
      }
      else removeAssignments(morphism, new_assignments);
   }
   return false;
}


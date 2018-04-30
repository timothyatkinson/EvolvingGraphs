#include "a_node_removeActiveEdge.h"

#include "a_node.h"

static bool match_n1(Morphism *morphism);
static bool match_e0(Morphism *morphism);
static bool match_n0(Morphism *morphism, Edge *host_edge);

bool matcha_node_removeActiveEdge(Morphism *morphism)
{
   if(2 > a_node_host->number_of_nodes || 1 > a_node_host->number_of_edges) return false;
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
      if(host_node->indegree < 0 || host_node->outdegree < 1 ||
         ((host_node->outdegree + host_node->indegree - 1 - 0 - 0) < 0)) continue;

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
         if(match_e0(morphism)) return true;
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

static bool match_e0(Morphism *morphism)
{
   /* Start node is the already-matched node from which the candidate
      edges are drawn. End node may or may not have been matched already. */
   int start_index = lookupNode(morphism, 1);
   int end_index = lookupNode(morphism, 0);
   if(start_index < 0) return false;
   Node *host_node = getNode(a_node_host, start_index);

   int counter;
   for(counter = 0; counter < host_node->out_edges.size + 2; counter++)
   {
      Edge *host_edge = getNthOutEdge(a_node_host, host_node, counter);
      if(host_edge == NULL) continue;
      if(host_edge->matched) continue;
      if(host_edge->source == host_edge->target) continue;
      if(host_edge->label.mark != 5) continue;

      /* If the end node has been matched, check that the target of the
       * host edge is the image of the end node. */
      if(end_index >= 0)
      {
         if(host_edge->target != end_index) continue;
      }
      /* Otherwise, the target of the host edge should be unmatched. */
      else
      {
         Node *end_node = getNode(a_node_host, host_edge->target);
         if(end_node->matched) continue;
      }

      HostLabel label = host_edge->label;
      bool match = false;
      /* Label Matching */
      int new_assignments = 0;
      /* Matching the empty list. */
      match = label.length == 0 ? true : false;
      if(match)
      {
         addEdgeMap(morphism, 0, host_edge->index, new_assignments);
         host_edge->matched = true;
         if(match_n0(morphism, host_edge)) return true;
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

static bool match_n0(Morphism *morphism, Edge *host_edge)
{
   Node *host_node = getTarget(a_node_host, host_edge);

   if(host_node->matched) return false;
   if(host_node->label.mark != 0) return false;
      if(host_node->indegree < 1 || host_node->outdegree < 0 ||
         ((host_node->outdegree + host_node->indegree - 0 - 1 - 0) < 0)) return false;;

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
      /* All items matched! */
         return true;
   }
   else removeAssignments(morphism, new_assignments);
   return false;
}

void applya_node_removeActiveEdge(Morphism *morphism, bool record_changes)
{
   int host_edge_index = lookupEdge(morphism, 0);
   if(record_changes)
   {
      Edge *edge = getEdge(a_node_host, host_edge_index);
      /* A hole is created if the edge is not at the right-most index of the array. */
      pushRemovedEdge(edge->label, edge->source, edge->target, edge->index,
                      edge->index < a_node_host->edges.size - 1);
   }
   removeEdge(a_node_host, host_edge_index);

   /* Reset the morphism. */
   initialiseMorphism(morphism, a_node_host);
}

static bool fillpot_n1(MorphismPot *pot, Morphism *morphism);
static bool fillpot_e0(MorphismPot *pot, Morphism *morphism);
static bool fillpot_n0(MorphismPot *pot, Morphism *morphism, Edge *host_edge);

bool fillpota_node_removeActiveEdge(MorphismPot *pot, Morphism *morphism)
{
   if(2 > a_node_host->number_of_nodes || 1 > a_node_host->number_of_edges) return false;
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
      if(host_node->indegree < 0 || host_node->outdegree < 1 ||
         ((host_node->outdegree + host_node->indegree - 1 - 0 - 0) < 0)) continue;

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
         if(fillpot_e0(pot, morphism)) return true;
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

static bool fillpot_e0(MorphismPot *pot, Morphism *morphism)
{
   /* Start node is the already-matched node from which the candidate
      edges are drawn. End node may or may not have been matched already. */
   int start_index = lookupNode(morphism, 1);
   int end_index = lookupNode(morphism, 0);
   if(start_index < 0) return false;
   Node *host_node = getNode(a_node_host, start_index);

   int counter;
   for(counter = 0; counter < host_node->out_edges.size + 2; counter++)
   {
      Edge *host_edge = getNthOutEdge(a_node_host, host_node, counter);
      if(host_edge == NULL) continue;
      if(host_edge->matched) continue;
      if(host_edge->source == host_edge->target) continue;
      if(host_edge->label.mark != 5) continue;

      /* If the end node has been matched, check that the target of the
       * host edge is the image of the end node. */
      if(end_index >= 0)
      {
         if(host_edge->target != end_index) continue;
      }
      /* Otherwise, the target of the host edge should be unmatched. */
      else
      {
         Node *end_node = getNode(a_node_host, host_edge->target);
         if(end_node->matched) continue;
      }

      HostLabel label = host_edge->label;
      bool match = false;
      /* Label Matching */
      int new_assignments = 0;
      /* Matching the empty list. */
      match = label.length == 0 ? true : false;
      if(match)
      {
         addEdgeMap(morphism, 0, host_edge->index, new_assignments);
         host_edge->matched = true;
         if(fillpot_n0(pot, morphism, host_edge)) return true;
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

static bool fillpot_n0(MorphismPot *pot, Morphism *morphism, Edge *host_edge)
{
   Node *host_node = getTarget(a_node_host, host_edge);

   if(host_node->matched) return false;
   if(host_node->label.mark != 0) return false;
      if(host_node->indegree < 1 || host_node->outdegree < 0 ||
         ((host_node->outdegree + host_node->indegree - 0 - 1 - 0) < 0)) return false;;

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
      /* All items matched! */
         putMorphism(pot, morphism, "a_node_removeActiveEdge", a_node_host);
         removeNodeMap(morphism, 0);
         host_node->matched = false;
   }
   else removeAssignments(morphism, new_assignments);
   return false;
}


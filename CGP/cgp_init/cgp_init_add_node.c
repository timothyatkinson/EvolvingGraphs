#include "cgp_init_add_node.h"

#include "cgp_init.h"

static bool match_n0(Morphism *morphism);

bool matchcgp_init_add_node(Morphism *morphism)
{
   if(1 > cgp_init_host->number_of_nodes || 0 > cgp_init_host->number_of_edges) return false;
   if(match_n0(morphism)) return true;
   else
   {
      initialiseMorphism(morphism, cgp_init_host);
      return false;
   }
}

static bool match_n0(Morphism *morphism)
{
   int host_index;
   for(host_index = 0; host_index < cgp_init_host->nodes.size; host_index++)
   {
      Node *host_node = getNode(cgp_init_host, host_index);
      if(host_node == NULL || host_node->index == -1) continue;
      if(host_node->matched) continue;
      if(host_node->label.mark != 0) continue;
      if(host_node->indegree < 0 || host_node->outdegree < 0 ||
         ((host_node->outdegree + host_node->indegree - 0 - 0 - 0) < 0)) continue;

      HostLabel label = host_node->label;
      bool match = false;
      /* Label Matching */
      int new_assignments = 0;
      /* Matching the empty list. */
      match = label.length == 0 ? true : false;
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

void applycgp_init_add_node(Morphism *morphism, bool record_changes)
{
   int host_node_index;
   int node_array_size1 = cgp_init_host->nodes.size;
   host_node_index = addNode(cgp_init_host, 0, blank_label);
   /* If the node array size has not increased after the node addition, then
      the node was added to a hole in the array. */
   if(record_changes)
      pushAddedNode(host_node_index, node_array_size1 == cgp_init_host->nodes.size);
   /* Reset the morphism. */
   initialiseMorphism(morphism, cgp_init_host);
}

static bool fillpot_n0(MorphismPot *pot, Morphism *morphism);

bool fillpotcgp_init_add_node(MorphismPot *pot, Morphism *morphism)
{
   if(1 > cgp_init_host->number_of_nodes || 0 > cgp_init_host->number_of_edges) return false;
   int oldPotsize = potSize(pot);
   morphism->weight = 0.000000;
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
   int host_index;
   for(host_index = 0; host_index < cgp_init_host->nodes.size; host_index++)
   {
      Node *host_node = getNode(cgp_init_host, host_index);
      if(host_node == NULL || host_node->index == -1) continue;
      if(host_node->matched) continue;
      if(host_node->label.mark != 0) continue;
      if(host_node->indegree < 0 || host_node->outdegree < 0 ||
         ((host_node->outdegree + host_node->indegree - 0 - 0 - 0) < 0)) continue;

      HostLabel label = host_node->label;
      bool match = false;
      /* Label Matching */
      int new_assignments = 0;
      /* Matching the empty list. */
      match = label.length == 0 ? true : false;
      if(match)
      {
         addNodeMap(morphism, 0, host_node->index, new_assignments);
         host_node->matched = true;
         /* All items matched! */
            putMorphism(pot, morphism, "cgp_init_add_node", cgp_init_host);
            removeNodeMap(morphism, 0);
            host_node->matched = false;
      }
      else removeAssignments(morphism, new_assignments);
   }
   return false;
}


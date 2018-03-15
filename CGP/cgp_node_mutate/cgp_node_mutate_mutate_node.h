#include "graph.h"
#include "label.h"
#include "graphStacks.h"
#include "parser.h"
#include "morphism.h"

bool matchcgp_node_mutate_mutate_node(Morphism *morphism);

void applycgp_node_mutate_mutate_node(Morphism *morphism, bool record_changes);
bool fillpotcgp_node_mutate_mutate_node(MorphismPot *pot, Morphism *morphism);


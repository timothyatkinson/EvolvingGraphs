#include "graph.h"
#include "label.h"
#include "graphStacks.h"
#include "parser.h"
#include "morphism.h"

bool matchcgp_init_add_node(Morphism *morphism);

void applycgp_init_add_node(Morphism *morphism, bool record_changes);
bool fillpotcgp_init_add_node(MorphismPot *pot, Morphism *morphism);


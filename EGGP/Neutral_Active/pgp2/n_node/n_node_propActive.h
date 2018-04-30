#include "graph.h"
#include "label.h"
#include "graphStacks.h"
#include "parser.h"
#include "morphism.h"

bool matchn_node_propActive(Morphism *morphism);

void applyn_node_propActive(Morphism *morphism, bool record_changes);
bool fillpotn_node_propActive(MorphismPot *pot, Morphism *morphism);


#include "graph.h"
#include "label.h"
#include "graphStacks.h"
#include "parser.h"
#include "morphism.h"

bool matchn_node_removeActive(Morphism *morphism);

void applyn_node_removeActive(Morphism *morphism, bool record_changes);
bool fillpotn_node_removeActive(MorphismPot *pot, Morphism *morphism);


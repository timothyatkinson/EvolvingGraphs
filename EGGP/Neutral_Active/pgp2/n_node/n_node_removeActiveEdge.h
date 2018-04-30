#include "graph.h"
#include "label.h"
#include "graphStacks.h"
#include "parser.h"
#include "morphism.h"

bool matchn_node_removeActiveEdge(Morphism *morphism);

void applyn_node_removeActiveEdge(Morphism *morphism, bool record_changes);
bool fillpotn_node_removeActiveEdge(MorphismPot *pot, Morphism *morphism);


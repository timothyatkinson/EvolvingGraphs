#include "graph.h"
#include "label.h"
#include "graphStacks.h"
#include "parser.h"
#include "morphism.h"

bool matchn_node_initActiveNode(Morphism *morphism);

void applyn_node_initActiveNode(Morphism *morphism, bool record_changes);
bool fillpotn_node_initActiveNode(MorphismPot *pot, Morphism *morphism);


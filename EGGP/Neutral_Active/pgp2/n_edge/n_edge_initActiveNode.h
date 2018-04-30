#include "graph.h"
#include "label.h"
#include "graphStacks.h"
#include "parser.h"
#include "morphism.h"

bool matchn_edge_initActiveNode(Morphism *morphism);

void applyn_edge_initActiveNode(Morphism *morphism, bool record_changes);
bool fillpotn_edge_initActiveNode(MorphismPot *pot, Morphism *morphism);


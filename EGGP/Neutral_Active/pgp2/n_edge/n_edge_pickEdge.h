#include "graph.h"
#include "label.h"
#include "graphStacks.h"
#include "parser.h"
#include "morphism.h"

bool matchn_edge_pickEdge(Morphism *morphism);

void applyn_edge_pickEdge(Morphism *morphism, bool record_changes);
bool fillpotn_edge_pickEdge(MorphismPot *pot, Morphism *morphism);


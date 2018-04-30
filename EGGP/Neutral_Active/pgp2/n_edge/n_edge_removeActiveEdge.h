#include "graph.h"
#include "label.h"
#include "graphStacks.h"
#include "parser.h"
#include "morphism.h"

bool matchn_edge_removeActiveEdge(Morphism *morphism);

void applyn_edge_removeActiveEdge(Morphism *morphism, bool record_changes);
bool fillpotn_edge_removeActiveEdge(MorphismPot *pot, Morphism *morphism);


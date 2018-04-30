#include "graph.h"
#include "label.h"
#include "graphStacks.h"
#include "parser.h"
#include "morphism.h"

bool matchn_edge_mutateEdge(Morphism *morphism);

void applyn_edge_mutateEdge(Morphism *morphism, bool record_changes);
bool fillpotn_edge_mutateEdge(MorphismPot *pot, Morphism *morphism);


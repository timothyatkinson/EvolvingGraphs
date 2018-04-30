#include "graph.h"
#include "label.h"
#include "graphStacks.h"
#include "parser.h"
#include "morphism.h"

bool matchn_edge_pickNewTarget(Morphism *morphism);

void applyn_edge_pickNewTarget(Morphism *morphism, bool record_changes);
bool fillpotn_edge_pickNewTarget(MorphismPot *pot, Morphism *morphism);


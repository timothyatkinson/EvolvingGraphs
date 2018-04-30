#include "graph.h"
#include "label.h"
#include "graphStacks.h"
#include "parser.h"
#include "morphism.h"

bool matchn_edge_markOutputs(Morphism *morphism);

void applyn_edge_markOutputs(Morphism *morphism, bool record_changes);
bool fillpotn_edge_markOutputs(MorphismPot *pot, Morphism *morphism);


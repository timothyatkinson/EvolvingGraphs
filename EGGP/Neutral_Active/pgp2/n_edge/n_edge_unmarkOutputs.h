#include "graph.h"
#include "label.h"
#include "graphStacks.h"
#include "parser.h"
#include "morphism.h"

bool matchn_edge_unmarkOutputs(Morphism *morphism);

void applyn_edge_unmarkOutputs(Morphism *morphism, bool record_changes);
bool fillpotn_edge_unmarkOutputs(MorphismPot *pot, Morphism *morphism);


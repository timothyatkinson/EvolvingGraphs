#include "graph.h"
#include "label.h"
#include "graphStacks.h"
#include "parser.h"
#include "morphism.h"

bool matcheggp_dc_edge_unmarkOutputs(Morphism *morphism);

void applyeggp_dc_edge_unmarkOutputs(Morphism *morphism, bool record_changes);
bool fillpoteggp_dc_edge_unmarkOutputs(MorphismPot *pot, Morphism *morphism);


#include "graph.h"
#include "label.h"
#include "graphStacks.h"
#include "parser.h"
#include "morphism.h"

bool matchn_edge_outActive(Morphism *morphism);

void applyn_edge_outActive(Morphism *morphism, bool record_changes);
bool fillpotn_edge_outActive(MorphismPot *pot, Morphism *morphism);


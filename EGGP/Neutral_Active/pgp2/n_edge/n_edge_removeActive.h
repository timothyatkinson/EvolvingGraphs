#include "graph.h"
#include "label.h"
#include "graphStacks.h"
#include "parser.h"
#include "morphism.h"

bool matchn_edge_removeActive(Morphism *morphism);

void applyn_edge_removeActive(Morphism *morphism, bool record_changes);
bool fillpotn_edge_removeActive(MorphismPot *pot, Morphism *morphism);


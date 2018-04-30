#include "graph.h"
#include "label.h"
#include "graphStacks.h"
#include "parser.h"
#include "morphism.h"

bool matchn_edge_propActive(Morphism *morphism);

void applyn_edge_propActive(Morphism *morphism, bool record_changes);
bool fillpotn_edge_propActive(MorphismPot *pot, Morphism *morphism);


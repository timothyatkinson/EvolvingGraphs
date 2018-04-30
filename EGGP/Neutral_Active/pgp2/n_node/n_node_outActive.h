#include "graph.h"
#include "label.h"
#include "graphStacks.h"
#include "parser.h"
#include "morphism.h"

bool matchn_node_outActive(Morphism *morphism);

void applyn_node_outActive(Morphism *morphism, bool record_changes);
bool fillpotn_node_outActive(MorphismPot *pot, Morphism *morphism);


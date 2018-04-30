#include "graph.h"
#include "label.h"
#include "graphStacks.h"
#include "parser.h"
#include "morphism.h"

bool matchn_node_pickNode(Morphism *morphism);

void applyn_node_pickNode(Morphism *morphism, bool record_changes);
bool fillpotn_node_pickNode(MorphismPot *pot, Morphism *morphism);


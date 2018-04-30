#include "graph.h"
#include "label.h"
#include "graphStacks.h"
#include "parser.h"
#include "morphism.h"

bool matchn_node_mutateNode(Morphism *morphism);

void applyn_node_mutateNode(Morphism *morphism, bool record_changes);
bool fillpotn_node_mutateNode(MorphismPot *pot, Morphism *morphism);


#include "graph.h"
#include "label.h"
#include "graphStacks.h"
#include "parser.h"
#include "morphism.h"

bool matcha_node_mutateNode(Morphism *morphism);

void applya_node_mutateNode(Morphism *morphism, bool record_changes);
bool fillpota_node_mutateNode(MorphismPot *pot, Morphism *morphism);


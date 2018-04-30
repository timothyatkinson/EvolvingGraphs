#include "graph.h"
#include "label.h"
#include "graphStacks.h"
#include "parser.h"
#include "morphism.h"

bool matcha_node_initActiveNode(Morphism *morphism);

void applya_node_initActiveNode(Morphism *morphism, bool record_changes);
bool fillpota_node_initActiveNode(MorphismPot *pot, Morphism *morphism);


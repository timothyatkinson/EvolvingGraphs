#include "graph.h"
#include "label.h"
#include "graphStacks.h"
#include "parser.h"
#include "morphism.h"

bool matcha_node_removeActive(Morphism *morphism);

void applya_node_removeActive(Morphism *morphism, bool record_changes);
bool fillpota_node_removeActive(MorphismPot *pot, Morphism *morphism);


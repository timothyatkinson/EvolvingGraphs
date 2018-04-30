#include "graph.h"
#include "label.h"
#include "graphStacks.h"
#include "parser.h"
#include "morphism.h"

bool matcha_node_removeActiveEdge(Morphism *morphism);

void applya_node_removeActiveEdge(Morphism *morphism, bool record_changes);
bool fillpota_node_removeActiveEdge(MorphismPot *pot, Morphism *morphism);


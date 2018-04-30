#include "graph.h"
#include "label.h"
#include "graphStacks.h"
#include "parser.h"
#include "morphism.h"

bool matcha_edge_removeActiveEdge(Morphism *morphism);

void applya_edge_removeActiveEdge(Morphism *morphism, bool record_changes);
bool fillpota_edge_removeActiveEdge(MorphismPot *pot, Morphism *morphism);


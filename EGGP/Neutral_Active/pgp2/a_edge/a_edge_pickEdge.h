#include "graph.h"
#include "label.h"
#include "graphStacks.h"
#include "parser.h"
#include "morphism.h"

bool matcha_edge_pickEdge(Morphism *morphism);

void applya_edge_pickEdge(Morphism *morphism, bool record_changes);
bool fillpota_edge_pickEdge(MorphismPot *pot, Morphism *morphism);


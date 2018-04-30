#include "graph.h"
#include "label.h"
#include "graphStacks.h"
#include "parser.h"
#include "morphism.h"

bool matcha_edge_removeActive(Morphism *morphism);

void applya_edge_removeActive(Morphism *morphism, bool record_changes);
bool fillpota_edge_removeActive(MorphismPot *pot, Morphism *morphism);


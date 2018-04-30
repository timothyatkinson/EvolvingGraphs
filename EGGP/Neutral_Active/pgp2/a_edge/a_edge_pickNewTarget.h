#include "graph.h"
#include "label.h"
#include "graphStacks.h"
#include "parser.h"
#include "morphism.h"

bool matcha_edge_pickNewTarget(Morphism *morphism);

void applya_edge_pickNewTarget(Morphism *morphism, bool record_changes);
bool fillpota_edge_pickNewTarget(MorphismPot *pot, Morphism *morphism);


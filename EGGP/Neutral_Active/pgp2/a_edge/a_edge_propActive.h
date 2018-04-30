#include "graph.h"
#include "label.h"
#include "graphStacks.h"
#include "parser.h"
#include "morphism.h"

bool matcha_edge_propActive(Morphism *morphism);

void applya_edge_propActive(Morphism *morphism, bool record_changes);
bool fillpota_edge_propActive(MorphismPot *pot, Morphism *morphism);


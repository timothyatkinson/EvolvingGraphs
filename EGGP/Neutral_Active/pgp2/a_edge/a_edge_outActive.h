#include "graph.h"
#include "label.h"
#include "graphStacks.h"
#include "parser.h"
#include "morphism.h"

bool matcha_edge_outActive(Morphism *morphism);

void applya_edge_outActive(Morphism *morphism, bool record_changes);
bool fillpota_edge_outActive(MorphismPot *pot, Morphism *morphism);


#include "graph.h"
#include "label.h"
#include "graphStacks.h"
#include "parser.h"
#include "morphism.h"

bool matcha_node_outActive(Morphism *morphism);

void applya_node_outActive(Morphism *morphism, bool record_changes);
bool fillpota_node_outActive(MorphismPot *pot, Morphism *morphism);


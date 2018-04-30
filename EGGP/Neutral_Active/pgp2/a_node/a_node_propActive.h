#include "graph.h"
#include "label.h"
#include "graphStacks.h"
#include "parser.h"
#include "morphism.h"

bool matcha_node_propActive(Morphism *morphism);

void applya_node_propActive(Morphism *morphism, bool record_changes);
bool fillpota_node_propActive(MorphismPot *pot, Morphism *morphism);


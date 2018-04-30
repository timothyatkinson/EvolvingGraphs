#include "graph.h"
#include "label.h"
#include "graphStacks.h"
#include "parser.h"
#include "morphism.h"

bool matcha_edge_initActiveNode(Morphism *morphism);

void applya_edge_initActiveNode(Morphism *morphism, bool record_changes);
bool fillpota_edge_initActiveNode(MorphismPot *pot, Morphism *morphism);


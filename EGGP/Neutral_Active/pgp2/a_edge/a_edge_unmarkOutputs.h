#include "graph.h"
#include "label.h"
#include "graphStacks.h"
#include "parser.h"
#include "morphism.h"

bool matcha_edge_unmarkOutputs(Morphism *morphism);

void applya_edge_unmarkOutputs(Morphism *morphism, bool record_changes);
bool fillpota_edge_unmarkOutputs(MorphismPot *pot, Morphism *morphism);


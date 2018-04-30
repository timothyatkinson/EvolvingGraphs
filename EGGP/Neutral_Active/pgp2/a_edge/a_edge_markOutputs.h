#include "graph.h"
#include "label.h"
#include "graphStacks.h"
#include "parser.h"
#include "morphism.h"

bool matcha_edge_markOutputs(Morphism *morphism);

void applya_edge_markOutputs(Morphism *morphism, bool record_changes);
bool fillpota_edge_markOutputs(MorphismPot *pot, Morphism *morphism);


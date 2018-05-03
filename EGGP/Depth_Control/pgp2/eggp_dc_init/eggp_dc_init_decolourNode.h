#include "graph.h"
#include "label.h"
#include "graphStacks.h"
#include "parser.h"
#include "morphism.h"

bool matcheggp_dc_init_decolourNode(Morphism *morphism);

void applyeggp_dc_init_decolourNode(Morphism *morphism, bool record_changes);
bool fillpoteggp_dc_init_decolourNode(MorphismPot *pot, Morphism *morphism);


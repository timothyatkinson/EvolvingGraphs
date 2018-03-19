#include "graph.h"
#include "label.h"
#include "graphStacks.h"
#include "parser.h"
#include "morphism.h"

bool matchcgp_init_connect_output(Morphism *morphism);

void applycgp_init_connect_output(Morphism *morphism, bool record_changes);
bool fillpotcgp_init_connect_output(MorphismPot *pot, Morphism *morphism);


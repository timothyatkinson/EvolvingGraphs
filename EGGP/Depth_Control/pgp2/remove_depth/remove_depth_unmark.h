#include "graph.h"
#include "label.h"
#include "graphStacks.h"
#include "parser.h"
#include "morphism.h"

bool matchremove_depth_unmark(Morphism *morphism);

void applyremove_depth_unmark(Morphism *morphism, bool record_changes);
bool fillpotremove_depth_unmark(MorphismPot *pot, Morphism *morphism);


#include "graph.h"
#include "label.h"
#include "graphStacks.h"
#include "parser.h"
#include "morphism.h"

bool matchremove_depth_removeDepth(Morphism *morphism);

void applyremove_depth_removeDepth(Morphism *morphism, bool record_changes);
bool fillpotremove_depth_removeDepth(MorphismPot *pot, Morphism *morphism);


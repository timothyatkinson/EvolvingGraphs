#include "graph.h"
#include "label.h"
#include "graphStacks.h"
#include "parser.h"
#include "morphism.h"

bool matchadd_depth_incIn(Morphism *morphism);

void applyadd_depth_incIn(Morphism *morphism, bool record_changes);
bool fillpotadd_depth_incIn(MorphismPot *pot, Morphism *morphism);


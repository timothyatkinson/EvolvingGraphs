#include "graph.h"
#include "label.h"
#include "graphStacks.h"
#include "parser.h"
#include "morphism.h"

bool matchadd_depth_incOut(Morphism *morphism);

void applyadd_depth_incOut(Morphism *morphism, bool record_changes);
bool fillpotadd_depth_incOut(MorphismPot *pot, Morphism *morphism);


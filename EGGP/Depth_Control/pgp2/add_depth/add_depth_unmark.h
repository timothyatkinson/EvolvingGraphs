#include "graph.h"
#include "label.h"
#include "graphStacks.h"
#include "parser.h"
#include "morphism.h"

bool matchadd_depth_unmark(Morphism *morphism);

void applyadd_depth_unmark(Morphism *morphism, bool record_changes);
bool fillpotadd_depth_unmark(MorphismPot *pot, Morphism *morphism);


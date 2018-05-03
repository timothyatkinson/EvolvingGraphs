#include "graph.h"
#include "label.h"
#include "graphStacks.h"
#include "parser.h"
#include "morphism.h"

bool matchadd_depth_initNode(Morphism *morphism);

void applyadd_depth_initNode(Morphism *morphism, bool record_changes);
bool fillpotadd_depth_initNode(MorphismPot *pot, Morphism *morphism);


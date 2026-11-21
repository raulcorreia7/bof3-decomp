#include "area121_14.h"

/* Each access reloads the work cell: the stores go through its pointer, which
 * the compiler must assume may alias the cell. */

#include "overlays/area/shared/Area_InitSceneActor.h"

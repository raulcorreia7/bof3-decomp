#include "area088_13.h"

/* Each access reloads the work cell: the stores go through its pointer, which
 * the compiler must assume may alias the cell. */
#include "overlays/area/Area_StartCellActor.h"

MATCH void func_801F5170(void) {
    AREA_START_CELL_ACTOR(D_801F591C, D_801F591D);
}

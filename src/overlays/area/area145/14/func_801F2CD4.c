#include "area145_14.h"

MATCH void func_801F2CD4(void) {
    TASK(Actor)->pos.x.fixed = TO_COORD(49) + COORD_HALF;
    TASK(Actor)->pos.y.fixed = TO_COORD(99) + COORD_HALF;
    TASK(Actor)->gravity     = 0x500000;
    TASK(Actor)->vz          = 5242880;
    SND_SEQueueSelection(0x208);
    TASK(Actor)->header.mode++;
    TASK(Actor)->header.step = 0;
}

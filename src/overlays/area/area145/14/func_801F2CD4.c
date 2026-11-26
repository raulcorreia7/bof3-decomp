#include "area145_14.h"

MATCH void func_801F2CD4(void) {
    SELF(Actor)->pos.x.fixed = TO_COORD(49) + COORD_HALF;
    SELF(Actor)->pos.y.fixed = TO_COORD(99) + COORD_HALF;
    SELF(Actor)->gravity     = 0x500000;
    SELF(Actor)->vz          = 5242880;
    SND_SEQueueSelection(0x208);
    SELF(Actor)->header.mode++;
    SELF(Actor)->header.step = 0;
}

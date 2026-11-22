#include "area048_13.h"

MATCH void func_801F4148(void) {
    func_801F41F0(COORD_INT(TASK(Actor)->pos.x), D_801F4E74[TASK(Actor)->timer >> 1]);
    TASK(Actor)->timer++;
    if (TASK(Actor)->timer >= 7) {
        TASK(Actor)->timer       = 0;
        TASK(Actor)->header.step = 3;
    }
    func_801F4258(COORD_INT(TASK(Actor)->pos.x));
}

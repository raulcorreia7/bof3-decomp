#include "area048_13.h"

MATCH void func_801F40B4(void) {
    func_801F41F0(COORD_INT(TASK(Actor)->pos.x), D_801F4E70[(u8)(TASK(Actor)->timer / 3)]);
    TASK(Actor)->timer++;
    if (TASK(Actor)->timer >= 4) {
        TASK(Actor)->header.step = 1;
    }
}

#include "area077_14.h"

MATCH void func_801F3CB8(void) {
    WorldPos_Copy(&TASK(Actor)->pos, &D_80146954);
    TASK(Actor)->vx = 180;
    func_801F41B4();
    TASK(Actor)->header.mode++;
}

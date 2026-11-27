#include "area077_14.h"

MATCH void func_801F3CB8(void) {
    WorldPos_Copy(&SELF(Actor)->pos, &D_80146954);
    SELF(Actor)->vx = 180;
    func_801F41B4();
    SELF(Actor)->header.mode++;
}

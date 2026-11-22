#include "area042_13.h"

MATCH void func_801F3BF8(void) {
    Area_SetPosX(D_801F5350[(u8)(TASK(Actor)->timer / 3)]);
    TASK(Actor)->timer++;
    if (TASK(Actor)->timer >= 4) {
        TASK(Actor)->header.step = 1;
    }
}

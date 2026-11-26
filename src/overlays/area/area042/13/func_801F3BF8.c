#include "area042_13.h"

MATCH void func_801F3BF8(void) {
    Area_SetPosX(D_801F5350[(u8)(SELF(Actor)->timer / 3)]);
    SELF(Actor)->timer++;
    if (SELF(Actor)->timer >= 4) {
        SELF(Actor)->header.step = 1;
    }
}

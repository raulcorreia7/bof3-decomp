#include "area077_14.h"

MATCH void func_801F5710(void) {
    Area_PaletteCopyRow(3, (SELF(Actor)->timer >> 1) + 5, 3, 3);
    Area_PaletteCopyRow(6, (SELF(Actor)->timer >> 1) + 0xB, 6, 9);
    SELF(Actor)->timer += 1;
    if (SELF(Actor)->timer >= 6U) {
        SELF(Actor)->header.step += 1;
    }
}

#include "area077_14.h"

MATCH void func_801F5710(void) {
    Area_PaletteCopyRow(3, (TASK(Actor)->timer >> 1) + 5, 3, 3);
    Area_PaletteCopyRow(6, (TASK(Actor)->timer >> 1) + 0xB, 6, 9);
    TASK(Actor)->timer += 1;
    if (TASK(Actor)->timer >= 6U) {
        TASK(Actor)->header.step += 1;
    }
}

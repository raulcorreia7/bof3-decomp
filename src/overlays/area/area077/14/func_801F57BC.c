#include "area077_14.h"

MATCH void func_801F57BC(void) {
    Area_PaletteCopyRow(0x3, D_801F62CC[TASK(Actor)->timer & 3], 3, 3);
    Area_PaletteCopyRow(7, D_801F62DC[TASK(Actor)->timer & 0x3], 6, 9);
    Area_PaletteCopyRow(7, D_801F62DC[TASK(Actor)->timer & 0x3] + 1, 6, 10);
    TASK(Actor)->timer++;
}

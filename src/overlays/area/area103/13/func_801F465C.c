#include "area103_13.h"

MATCH void func_801F465C(void) {
    s16 count;

    if (TASK(Actor)->timer == 15) {
        TASK(Actor)->timer = 0;
    }
    count = TASK(Actor)->unk_32;
    if (count > 0) {
        TASK(Actor)->unk_32 = count - 1;
    } else if (!((TASK(Actor)->timer / 5) & BYTE_MASK)) {
        TASK(Actor)->header.step += 1;
    }
    if (!((TASK(Actor)->timer % 5) & BYTE_MASK)) {
        func_801F4E70(((TASK(Actor)->timer / 5) & BYTE_MASK) + 7);
    }
    TASK(Actor)->timer += 1;
    Area_CellSetPalette(66, (s16)(((s16)TASK(Actor)->unk_32 / 6) + 0x18));
}

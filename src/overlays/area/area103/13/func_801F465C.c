#include "area103_13.h"

MATCH void func_801F465C(void) {
    s16 count;

    if (SELF(Actor)->timer == 15) {
        SELF(Actor)->timer = 0;
    }
    count = SELF(Actor)->unk_32;
    if (count > 0) {
        SELF(Actor)->unk_32 = count - 1;
    } else if (!((SELF(Actor)->timer / 5) & BYTE_MASK)) {
        SELF(Actor)->header.step += 1;
    }
    if (!((SELF(Actor)->timer % 5) & BYTE_MASK)) {
        func_801F4E70(((SELF(Actor)->timer / 5) & BYTE_MASK) + 7);
    }
    SELF(Actor)->timer += 1;
    Area_CellSetPalette(66, (s16)(((s16)SELF(Actor)->unk_32 / 6) + 0x18));
}

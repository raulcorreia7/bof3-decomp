#include "area103_13.h"

MATCH void func_801F37A0(void) {
    s32 limit;

    SELF(Actor)->unk_1C += 0x1000000;
    limit = SELF(Actor)->vz + 0x8000000;
    if (limit < SELF(Actor)->unk_1C) {
        SELF(Actor)->unk_1C = limit;
    }
    /* FAKE: gravity is s32 but asm accesses offset 0x20 as u16 */
    FIELD(u16, g_Self, 0x20) -= 0x200;
    func_801F38DC();
    if (--SELF(Actor)->timer == 0) {
        SELF(Actor)->timer = 16;
        SELF(Actor)->header.mode += 1;
    }
}

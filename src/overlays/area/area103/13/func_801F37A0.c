#include "area103_13.h"

MATCH void func_801F37A0(void) {
    s32 limit;

    TASK(Actor)->unk_1C += 0x1000000;
    limit = TASK(Actor)->vz + 0x8000000;
    if (limit < TASK(Actor)->unk_1C) {
        TASK(Actor)->unk_1C = limit;
    }
    /* FAKE: gravity is s32 but asm accesses offset 0x20 as u16 */
    FIELD(u16, g_Task, 0x20) -= 0x200;
    func_801F38DC();
    if (--TASK(Actor)->timer == 0) {
        TASK(Actor)->timer = 16;
        TASK(Actor)->header.mode += 1;
    }
}

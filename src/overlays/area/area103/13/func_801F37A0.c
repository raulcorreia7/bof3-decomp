#include "area103_13.h"

MATCH void func_801F37A0(void) {
    s32 limit;

    g_Task->unk_1C += 0x1000000;
    limit = g_Task->vz + 0x8000000;
    if (limit < g_Task->unk_1C) {
        g_Task->unk_1C = limit;
    }
    /* FAKE: gravity is s32 but asm accesses offset 0x20 as u16 */
    FIELD(u16, g_Task, 0x20) -= 0x200;
    func_801F38DC();
    if (--g_Task->timer == 0) {
        g_Task->timer = 16;
        g_Task->header.mode += 1;
    }
}

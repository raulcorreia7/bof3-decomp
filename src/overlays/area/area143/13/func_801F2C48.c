#include "area143_13.h"

MATCH void func_801F2C48(void) {
    u8* work;

    work                   = (u8*)g_Task;
    FIELD(s32, work, 0x34) = g_Game.members[0].pos.x.fixed;
    FIELD(s32, work, 0x38) = g_Game.members[0].pos.y.fixed;
    FIELD(s32, work, 0x3C) = D_80145ECC;
    func_801F2D3C();
    func_801F2FE0();
    work = (u8*)g_Task;
    work[1]++;
}

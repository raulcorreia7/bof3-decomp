#include "area143_13.h"

MATCH void func_801F2C48(void) {
    u8* work;

    work                   = SELF(u8);
    FIELD(s32, work, 0x34) = g_Game.members[0].pos.x.fixed;
    FIELD(s32, work, 0x38) = g_Game.members[0].pos.y.fixed;
    FIELD(s32, work, 0x3C) = g_Game.members[0].pos.z.fixed;
    func_801F2D3C();
    func_801F2FE0();
    work = SELF(u8);
    work[1]++;
}

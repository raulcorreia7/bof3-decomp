#include "game_00.h"

MATCH void func_801B7EF0(void) {
    s32 value;

    COORD_INT(g_Task->z) = Area_ReadHeight(g_Task->x.fixed, g_Task->y.fixed) + 0x200;
    value                  = 0x3D;
    if (g_Task->direction_08 == 3) {
        value = 0x3C;
    }
    Actor_RequestScript(value);
    if (g_Task->unk_05 != 0) {
        func_801C2438();
        g_Task->tint.signed_bytes.unk_5D = -0x80;
        g_Task->tint.signed_bytes.unk_5E = -0x80;
        g_Task->tint.signed_bytes.unk_5F = -0x80;
        g_Task->tint.bytes.flags         = 1;
        g_Task->flags &= ~ACTOR_FLAG_HIDDEN;
        g_Task->unk_04 = 7;
    } else {
        g_Task->unk_04 = 8;
    }
}

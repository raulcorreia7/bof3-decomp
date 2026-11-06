#include "game_00.h"

MATCH void func_801B79F8(void) {
    COORD_INT(g_Task->z) = Area_ReadHeight(g_Task->x.fixed, g_Task->y.fixed) - 0x200;
    g_Task->x.fixed -= g_FacingOffsets[g_Task->direction_08].x * ((g_Task->state_70.byte + 1) << 5);
    g_Task->y.fixed -= g_FacingOffsets[g_Task->direction_08].y * ((g_Task->state_70.byte + 1) << 5);
    if (g_Task->direction_08 == 7) {
        Actor_RequestScript(0x3C);
    } else {
        Actor_RequestScript(0x3D);
    }
    if (g_Task->unk_05 != 0) {
        func_801C2438();
        g_Task->tint.signed_bytes.unk_5D = -0x80;
        g_Task->tint.signed_bytes.unk_5E = -0x80;
        g_Task->tint.signed_bytes.unk_5F = -0x80;
        g_Task->tint.bytes.flags         = 1;
        g_Task->header.flags &= ~ACTOR_FLAG_HIDDEN;
        g_Task->unk_04 = 3;
    } else {
        g_Task->unk_04 = 4;
    }
}

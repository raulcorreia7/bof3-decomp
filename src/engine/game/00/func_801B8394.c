#include "game_00.h"

MATCH void func_801B8394(void) {
    if (g_Task->state_70.byte != 0) {
        g_Task->pos.x.fixed -= g_FacingOffsets[g_Task->direction_08].x * 0x60;
        g_Task->pos.y.fixed -= g_FacingOffsets[g_Task->direction_08].y * 0x60;
        g_Task->unk_0A = 7;
    } else {
        g_Task->pos.x.fixed -= g_FacingOffsets[g_Task->direction_08].x * 0x40;
        g_Task->pos.y.fixed -= g_FacingOffsets[g_Task->direction_08].y * 0x40;
        g_Task->unk_0A = 5;
    }
    g_Task->timer                     = 0;
    COORD_INT(g_Task->pos.z)          = Area_ReadHeight(g_Task->pos.x.fixed, g_Task->pos.y.fixed);
    g_GameState->counter_11C.u8_value = 2;
    Actor_RequestScript(g_Task->direction_08 + 8);
    if (g_Task->unk_05 != 0) {
        func_801C2438();
        g_Task->tint.signed_bytes.unk_5D = -0x80;
        g_Task->tint.signed_bytes.unk_5E = -0x80;
        g_Task->tint.signed_bytes.unk_5F = -0x80;
        g_Task->tint.bytes.flags         = 1;
        g_Task->header.flags &= ~ACTOR_FLAG_HIDDEN;
        g_Task->unk_03 = 3;
    } else {
        g_Task->unk_03 = 4;
    }
}

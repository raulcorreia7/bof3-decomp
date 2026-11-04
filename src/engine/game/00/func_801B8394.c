#include "game_00.h"

MATCH void func_801B8394(void) {
    if (g_SpadWork->state_70.byte != 0) {
        g_SpadWork->x.fixed -= g_FacingOffsets[g_SpadWork->direction_08].x * 0x60;
        g_SpadWork->y.fixed -= g_FacingOffsets[g_SpadWork->direction_08].y * 0x60;
        g_SpadWork->unk_0A = 7;
    } else {
        g_SpadWork->x.fixed -= g_FacingOffsets[g_SpadWork->direction_08].x * 0x40;
        g_SpadWork->y.fixed -= g_FacingOffsets[g_SpadWork->direction_08].y * 0x40;
        g_SpadWork->unk_0A = 5;
    }
    g_SpadWork->unk_09                = 0;
    g_SpadWork->z.part.integer        = Area_ReadHeight(g_SpadWork->x.fixed, g_SpadWork->y.fixed);
    g_GameState->counter_11C.u8_value = 2;
    Actor_RequestScript(g_SpadWork->direction_08 + 8);
    if (g_SpadWork->unk_05 != 0) {
        func_801C2438();
        g_SpadWork->tint.signed_bytes.unk_5D = -0x80;
        g_SpadWork->tint.signed_bytes.unk_5E = -0x80;
        g_SpadWork->tint.signed_bytes.unk_5F = -0x80;
        g_SpadWork->tint.bytes.flags         = 1;
        g_SpadWork->flags_00 &= ~ACTOR_FLAG_HIDDEN;
        g_SpadWork->unk_03 = 3;
    } else {
        g_SpadWork->unk_03 = 4;
    }
}

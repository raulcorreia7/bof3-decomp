#include "game_00.h"

MATCH void func_801B79F8(void) {
    g_SpadWork->z.part.integer = Area_ReadHeight(g_SpadWork->x.fixed, g_SpadWork->y.fixed) - 0x200;
    g_SpadWork->x.fixed -= g_FacingOffsets[g_SpadWork->direction_08].x * ((g_SpadWork->state_70.byte + 1) << 5);
    g_SpadWork->y.fixed -= g_FacingOffsets[g_SpadWork->direction_08].y * ((g_SpadWork->state_70.byte + 1) << 5);
    if (g_SpadWork->direction_08 == 7) {
        Actor_RequestScript(0x3C);
    } else {
        Actor_RequestScript(0x3D);
    }
    if (g_SpadWork->unk_05 != 0) {
        func_801C2438();
        g_SpadWork->tint.signed_bytes.unk_5D = -0x80;
        g_SpadWork->tint.signed_bytes.unk_5E = -0x80;
        g_SpadWork->tint.signed_bytes.unk_5F = -0x80;
        g_SpadWork->tint.bytes.flags         = 1;
        g_SpadWork->flags_00 &= ~ACTOR_FLAG_HIDDEN;
        g_SpadWork->unk_04 = 3;
    } else {
        g_SpadWork->unk_04 = 4;
    }
}

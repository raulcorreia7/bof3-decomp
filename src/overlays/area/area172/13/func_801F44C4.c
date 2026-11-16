#include "area172_13.h"

#ifdef NON_MATCHING
NON_MATCHING void func_801F44C4(void) {
    s16 height;

    g_Task->vz += g_Task->gravity;
    Actor_UpdateMovement();
    height = Area_ReadHeight(g_Task->pos.x.fixed, g_Task->pos.y.fixed);
    if (COORD_INT(g_Task->pos.z) < height) {
        g_Task->header.flags &= ~0x20;
        g_Task->tint.bytes.flags     = 0;
        g_Task->tint.bytes.rgb.red   = 0;
        g_Task->tint.bytes.rgb.green = 0;
        g_Task->tint.bytes.rgb.blue  = 0;
        COORD_INT(g_Task->pos.z)     = height;
        g_Task->vz                   = 0;
        g_Task->gravity              = 0;
        g_Task->unk_04               = 2;
        Actor_SelectScript(0x39);
        g_ScriptState->unk_01 = 4;
    } else {
        g_ScriptState->cursor -= 2;
    }
    D_80145BD6[g_GameState->unk_13D * 12] -= 2;
    D_80145BD6[g_GameState->unk_13D * 12 + 1] -= 2;
    D_80145BD6[g_GameState->unk_13D * 12 + 2] -= 2;
    if (g_Task->tint.signed_bytes.delta.red != 0x40) {
        g_Task->tint.signed_bytes.delta.red += 4;
        g_Task->tint.bytes.rgb.green += 4;
        g_Task->tint.bytes.rgb.blue += 4;
    }
    D_80143F84 = g_Task->pos.z.fixed;
    Area_AdvanceScroll(COORD_INT(g_Task->pos.z));
}
#else
INCLUDE_ASM(func_801F44C4);
#endif

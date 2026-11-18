#include "area172_13.h"

/* Caller-side view: retail narrows the result into the height local through
 * the full word, so the call keeps its local s32 return view. */
MATCH void func_801F44C4(void) {
    s16 height;

    g_Task->vz += g_Task->gravity;
    Actor_UpdateMovement();
    height = ((s32 (*)(s32, s32))Area_ReadHeight)(g_Task->pos.x.fixed, g_Task->pos.y.fixed);
    if (COORD_INT(g_Task->pos.z) < height) {
        g_Task->header.flags &= ~0x20;
        g_Task->tint.bytes.flags = 0;
        g_Task->tint.bytes.rgb.r = 0;
        g_Task->tint.bytes.rgb.g = 0;
        g_Task->tint.bytes.rgb.b = 0;
        COORD_INT(g_Task->pos.z) = height;
        g_Task->vz               = 0;
        g_Task->gravity          = 0;
        g_Task->unk_04           = 2;
        Actor_SelectScript(0x39);
        g_ScriptState->unk_01 = 4;
    } else {
        g_ScriptState->cursor -= 2;
    }
    g_PaletteFades[g_GameState->palette_fade].offset.r -= 2;
    g_PaletteFades[g_GameState->palette_fade].offset.g -= 2;
    g_PaletteFades[g_GameState->palette_fade].offset.b -= 2;
    if (g_Task->tint.steps.delta.r != 0x40) {
        g_Task->tint.steps.delta.r += 4;
        g_Task->tint.bytes.rgb.g += 4;
        g_Task->tint.bytes.rgb.b += 4;
    }
    D_80143F84.fixed = g_Task->pos.z.fixed;
    Area_AdvanceScroll(COORD_INT(g_Task->pos.z));
}

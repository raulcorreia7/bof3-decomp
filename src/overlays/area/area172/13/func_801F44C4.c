#include "area172_13.h"

/* Caller-side view: retail narrows the result into the height local through
 * the full word, so the call keeps its local s32 return view. */
MATCH void func_801F44C4(void) {
    s16 height;

    TASK(Actor)->vz += TASK(Actor)->gravity;
    Actor_MovementUpdate();
    height = ((s32 (*)(s32, s32))Area_HeightRead)(TASK(Actor)->pos.x.fixed, TASK(Actor)->pos.y.fixed);
    if (COORD_INT(TASK(Actor)->pos.z) < height) {
        TASK(Actor)->header.flags &= ~0x20;
        TASK(Actor)->tint.bytes.flags = 0;
        TASK(Actor)->tint.bytes.rgb.r = 0;
        TASK(Actor)->tint.bytes.rgb.g = 0;
        TASK(Actor)->tint.bytes.rgb.b = 0;
        COORD_INT(TASK(Actor)->pos.z) = height;
        TASK(Actor)->vz               = 0;
        TASK(Actor)->gravity          = 0;
        TASK(Actor)->unk_04           = 2;
        Script_Select(0x39);
        g_ScriptState->unk_01 = 4;
    } else {
        g_ScriptState->cursor -= 2;
    }
    g_PaletteFades[g_GameState->palette_fade].offset.r -= 2;
    g_PaletteFades[g_GameState->palette_fade].offset.g -= 2;
    g_PaletteFades[g_GameState->palette_fade].offset.b -= 2;
    if (TASK(Actor)->tint.steps.delta.r != 0x40) {
        TASK(Actor)->tint.steps.delta.r += 4;
        TASK(Actor)->tint.bytes.rgb.g += 4;
        TASK(Actor)->tint.bytes.rgb.b += 4;
    }
    g_PartyPos.z.fixed = TASK(Actor)->pos.z.fixed;
    Area_ScrollAdvance(COORD_INT(TASK(Actor)->pos.z));
}

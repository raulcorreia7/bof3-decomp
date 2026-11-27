#include "area172_13.h"

/* Caller-side view: retail narrows the result into the height local through
 * the full word, so the call keeps its local s32 return view. */
MATCH void func_801F44C4(void) {
    s16 height;

    SELF(Actor)->vz += SELF(Actor)->gravity;
    Actor_MovementUpdate();
    height = ((s32 (*)(s32, s32))Area_HeightRead)(SELF(Actor)->pos.x.fixed, SELF(Actor)->pos.y.fixed);
    if (COORD_INT(SELF(Actor)->pos.z) < height) {
        SELF(Actor)->header.flags &= ~0x20;
        SELF(Actor)->tint.bytes.flags = 0;
        SELF(Actor)->tint.bytes.rgb.r = 0;
        SELF(Actor)->tint.bytes.rgb.g = 0;
        SELF(Actor)->tint.bytes.rgb.b = 0;
        COORD_INT(SELF(Actor)->pos.z) = height;
        SELF(Actor)->vz               = 0;
        SELF(Actor)->gravity          = 0;
        SELF(Actor)->unk_04           = 2;
        Script_Select(0x39);
        g_ScriptState->unk_01 = 4;
    } else {
        g_ScriptState->cursor -= 2;
    }
    g_PaletteFades[g_GameState->palette_fade].offset.r -= 2;
    g_PaletteFades[g_GameState->palette_fade].offset.g -= 2;
    g_PaletteFades[g_GameState->palette_fade].offset.b -= 2;
    if (SELF(Actor)->tint.steps.delta.r != 0x40) {
        SELF(Actor)->tint.steps.delta.r += 4;
        SELF(Actor)->tint.bytes.rgb.g += 4;
        SELF(Actor)->tint.bytes.rgb.b += 4;
    }
    g_PartyPos.z.fixed = SELF(Actor)->pos.z.fixed;
    Area_ScrollAdvance(COORD_INT(SELF(Actor)->pos.z));
}

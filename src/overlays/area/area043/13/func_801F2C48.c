#include "area043_13.h"

MATCH void func_801F2C48(void) {
    Actor* tint;

    g_CurrentActor->unk_93 = GFX_PaletteAllocFade(g_Self, 0, 0, 0, 1);
    SELF(Actor)->header.flags |= ACTOR_FLAG_SEMI_TRANSPARENT;
    /* The ActorTint word: its flags byte and three signed fade steps; unk_48, unk_04 and
     * unk_7E have no names. */
    tint                          = SELF(Actor);
    tint->tint.steps.delta.b      = -0x40;
    tint->tint.steps.delta.g      = -0x40;
    tint->tint.steps.delta.r      = -0x40;
    SELF(Actor)->tint.bytes.flags = 1;
    SELF(Actor)->unk_48           = 2;
    SELF(Actor)->unk_04           = 1;
    g_CurrentActor->unk_7E        = g_CurrentActor->unk_7E - 2;
}

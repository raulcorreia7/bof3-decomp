#include "game_00.h"

MATCH void func_801ACC08(void) {
    Actor* flags_set;
    Actor* flags_clear;
    Actor* tint;

    g_CurrentActor->unk_93 = GFX_PaletteAllocFade(SELF(Actor), 0U, 0U, 0U, 1);
    flags_set              = SELF(Actor);
    flags_set->header.flags |= 0x20;
    flags_clear = SELF(Actor);
    flags_clear->header.flags &= 0xBF;
    SELF(Actor)->tint.steps.flags = 1;
    tint                          = SELF(Actor);
    tint->tint.steps.delta.b      = -0x80;
    tint->tint.steps.delta.g      = -0x80;
    tint->tint.steps.delta.r      = -0x80;
    SELF(Actor)->unk_04           = 1;
    g_CurrentActor->unk_7E        = (g_CurrentActor->unk_7E - 1);
}

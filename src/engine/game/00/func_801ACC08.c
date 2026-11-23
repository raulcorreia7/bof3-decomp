#include "game_00.h"

MATCH void func_801ACC08(void) {
    Actor* flags_set;
    Actor* flags_clear;
    Actor* tint;

    g_CurrentActor->unk_93 = GFX_PaletteAllocFade(TASK(Actor), 0U, 0U, 0U, 1);
    flags_set              = TASK(Actor);
    flags_set->header.flags |= 0x20;
    flags_clear = TASK(Actor);
    flags_clear->header.flags &= 0xBF;
    TASK(Actor)->tint.steps.flags = 1;
    tint                          = TASK(Actor);
    tint->tint.steps.delta.b      = -0x80;
    tint->tint.steps.delta.g      = -0x80;
    tint->tint.steps.delta.r      = -0x80;
    TASK(Actor)->unk_04           = 1;
    g_CurrentActor->unk_7E        = (g_CurrentActor->unk_7E - 1);
}

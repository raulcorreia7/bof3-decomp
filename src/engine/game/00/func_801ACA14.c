#include "game_00.h"

MATCH void func_801ACA14(void) {
    Actor* flags_set;
    Actor* tint;
    Actor* work;

    g_CurrentActor->unk_93 = GFX_PaletteAllocFade(SELF(Actor), 0U, 0U, 0U, 1);
    flags_set              = SELF(Actor);
    flags_set->header.flags |= 0x20;
    tint                          = SELF(Actor);
    tint->tint.steps.delta.b      = -0x40;
    tint->tint.steps.delta.g      = -0x40;
    tint->tint.steps.delta.r      = -0x40;
    SELF(Actor)->tint.steps.flags = 1;
    work                          = SELF(Actor);
    g_CurrentActor->unk_7E        = (g_CurrentActor->unk_7E - 1);
    work->unk_04                  = 1;
}

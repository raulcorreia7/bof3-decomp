#include "game_00.h"

MATCH void func_801ACA14(void) {
    Actor* flags_set;
    Actor* tint;
    Actor* work;

    g_CurrentActor->unk_93 = GFX_PaletteAllocFade(TASK(Actor), 0U, 0U, 0U, 1);
    flags_set              = TASK(Actor);
    flags_set->header.flags |= 0x20;
    tint                          = TASK(Actor);
    tint->tint.steps.delta.b      = -0x40;
    tint->tint.steps.delta.g      = -0x40;
    tint->tint.steps.delta.r      = -0x40;
    TASK(Actor)->tint.steps.flags = 1;
    work                          = TASK(Actor);
    g_CurrentActor->unk_7E        = (g_CurrentActor->unk_7E - 1);
    work->unk_04                  = 1;
}

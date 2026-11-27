#include "game_00.h"

MATCH void func_801ACAC0(void) {
    Actor* work_5D;
    Actor* work_5E;
    Actor* work_flags;
    s8     tint_5D;
    s8     tint_5E;
    s8     tint_5F;

    work_5D = SELF(Actor);
    tint_5D = work_5D->tint.steps.delta.r;
    if (tint_5D != -0x80) {
        work_5D->tint.steps.delta.r = (tint_5D - 4);
    }
    work_5E = SELF(Actor);
    tint_5E = work_5E->tint.steps.delta.g;
    if (tint_5E != -0x80) {
        work_5E->tint.steps.delta.g = (tint_5E - 4);
    }
    tint_5F = SELF(Actor)->tint.steps.delta.b;
    if (tint_5F != -0x80) {
        SELF(Actor)->tint.steps.delta.b = (tint_5F - 4);
    }
    if ((SELF(Actor)->tint.raw & ~0xFF) == 0x80808000) {
        GFX_PaletteFreeFade(g_CurrentActor->unk_93);
        work_flags               = SELF(Actor);
        work_flags->header.flags = (work_flags->header.flags | 0x40);
        SELF(Actor)->unk_04      = 0;
        return;
    }
    g_CurrentActor->unk_7E = (g_CurrentActor->unk_7E - 1);
}

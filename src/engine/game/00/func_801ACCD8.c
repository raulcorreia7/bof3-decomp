#include "game_00.h"

MATCH void func_801ACCD8(void) {
    s8     tuneA;
    s8     tuneB;
    s8     tuneC;
    Actor* spad;
    Actor* spad2;
    Actor* spad3;
    Actor* spad4;

    spad  = TASK(Actor);
    tuneA = spad->tint.steps.delta.r;
    if (tuneA < -0x40) {
        spad->tint.steps.delta.r = (tuneA + 4);
    }
    spad2 = TASK(Actor);
    tuneB = spad2->tint.steps.delta.g;
    if (tuneB < -0x40) {
        spad2->tint.steps.delta.g = (tuneB + 4);
    }
    tuneC = TASK(Actor)->tint.steps.delta.b;
    if (tuneC < -0x40) {
        TASK(Actor)->tint.steps.delta.b = (tuneC + 4);
    }
    if ((TASK(Actor)->tint.raw & ~0xFF) == 0xC0C0C000) {
        GFX_PaletteFreeFade(g_CurrentActor->unk_93);
        spad3                         = TASK(Actor);
        spad3->header.flags           = (spad3->header.flags & 0xDF);
        TASK(Actor)->tint.bytes.flags = 0;
        spad4                         = TASK(Actor);
        spad4->tint.steps.delta.b     = 0;
        spad4->tint.steps.delta.g     = 0;
        spad4->tint.steps.delta.r     = 0;
        TASK(Actor)->unk_04           = 0;
        return;
    }
    g_CurrentActor->unk_7E = (g_CurrentActor->unk_7E - 1);
}

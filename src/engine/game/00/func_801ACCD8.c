#include "game_00.h"

MATCH void func_801ACCD8(void) {
    s8     tuneA;
    s8     tuneB;
    s8     tuneC;
    Actor* spad;
    Actor* spad2;
    Actor* spad3;
    Actor* spad4;

    spad  = g_Task;
    tuneA = spad->tint.steps.delta.r;
    if (tuneA < -0x40) {
        spad->tint.steps.delta.r = (tuneA + 4);
    }
    spad2 = g_Task;
    tuneB = spad2->tint.steps.delta.g;
    if (tuneB < -0x40) {
        spad2->tint.steps.delta.g = (tuneB + 4);
    }
    tuneC = g_Task->tint.steps.delta.b;
    if (tuneC < -0x40) {
        g_Task->tint.steps.delta.b = (tuneC + 4);
    }
    if ((g_Task->tint.raw & ~0xFF) == 0xC0C0C000) {
        GFX_PaletteFreeFade(g_CurrentActor->unk_93);
        spad3                     = g_Task;
        spad3->header.flags       = (spad3->header.flags & 0xDF);
        g_Task->tint.bytes.flags  = 0;
        spad4                     = g_Task;
        spad4->tint.steps.delta.b = 0;
        spad4->tint.steps.delta.g = 0;
        spad4->tint.steps.delta.r = 0;
        g_Task->unk_04            = 0;
        return;
    }
    g_CurrentActor->unk_7E = (g_CurrentActor->unk_7E - 1);
}

#include "area108_14.h"

MATCH s32 func_801F4C28(void) {
    s8     tuneA;
    s8     tuneB;
    s8     tuneC;
    Actor* spad;
    Actor* spad2;
    Actor* spad3;
    Actor* spad4;

    spad  = g_Task;
    tuneA = spad->tint.steps.delta.r;
    if (tuneA < -0x30) {
        spad->tint.steps.delta.r = (tuneA + 1);
    }
    spad2 = g_Task;
    tuneB = spad2->tint.steps.delta.g;
    if (tuneB < -0x30) {
        spad2->tint.steps.delta.g = (tuneB + 1);
        spad2                     = g_Task;
    }
    tuneC = spad2->tint.steps.delta.b;
    if (tuneC < -0x30) {
        spad2->tint.steps.delta.b = (tuneC + 1);
    }
    if ((g_Task->tint.raw & ~0xFF) == 0xD0D0D000) {
        GFX_PaletteFreeFade(g_CurrentActor->unk_93);
        spad3                    = g_Task;
        spad3->header.flags      = (spad3->header.flags & 0xDF);
        g_Task->tint.bytes.flags = 0;
        spad4                    = g_Task;
        spad4->tint.bytes.rgb.b  = 0;
        spad4->tint.bytes.rgb.g  = 0;
        spad4->tint.bytes.rgb.r  = 0;
        g_Task->unk_04           = 0;
        return;
    }
    g_CurrentActor->unk_7E = (g_CurrentActor->unk_7E - 2);
}

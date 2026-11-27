#include "area043_13.h"

MATCH void func_801F2D0C(void) {
    s8     tuneA;
    s8     tuneB;
    s8     tuneC;
    Actor* spad;
    Actor* spad2;

    spad  = SELF(Actor);
    tuneA = spad->tint.steps.delta.r;
    if (tuneA != -0x80) {
        spad->tint.steps.delta.r = (tuneA - 2);
    }
    spad2 = SELF(Actor);
    tuneB = spad2->tint.steps.delta.g;
    if (tuneB != -0x80) {
        spad2->tint.steps.delta.g = (tuneB - 2);
        spad2                     = SELF(Actor);
    }
    tuneC = spad2->tint.steps.delta.b;
    if (tuneC != -0x80) {
        spad2->tint.steps.delta.b = (tuneC - 2);
    }
    SELF(Actor)->scale.x += 2048;
    SELF(Actor)->scale.y += 2048;
    if ((SELF(Actor)->tint.raw & ~0xFF) == 0x80808000) {
        GFX_PaletteFreeFade(g_CurrentActor->unk_93);
        SELF(Actor)->header.flags |= 0x40;
        SELF(Actor)->unk_04 = 0;
    } else {
        g_CurrentActor->unk_7E -= 2;
    }
}

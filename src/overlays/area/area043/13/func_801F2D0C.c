#include "area043_13.h"

MATCH void func_801F2D0C(void) {
    s8     tuneA;
    s8     tuneB;
    s8     tuneC;
    Actor* spad;
    Actor* spad2;

    spad  = g_Task;
    tuneA = spad->tint.signed_bytes.unk_5D;
    if (tuneA != -0x80) {
        spad->tint.signed_bytes.unk_5D = (tuneA - 2);
    }
    spad2 = g_Task;
    tuneB = spad2->tint.signed_bytes.unk_5E;
    if (tuneB != -0x80) {
        spad2->tint.signed_bytes.unk_5E = (tuneB - 2);
        spad2                           = g_Task;
    }
    tuneC = spad2->tint.signed_bytes.unk_5F;
    if (tuneC != -0x80) {
        spad2->tint.signed_bytes.unk_5F = (tuneC - 2);
    }
    g_Task->scale.x += 2048;
    g_Task->scale.y += 2048;
    if ((g_Task->tint.word & ~0xFF) == 0x80808000) {
        GFX_FreePaletteFade(g_CurrentActor->unk_93);
        g_Task->header.flags |= 0x40;
        g_Task->unk_04 = 0;
    } else {
        g_CurrentActor->unk_7E -= 2;
    }
}

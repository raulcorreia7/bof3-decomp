#include "area108_14.h"

MATCH void func_801F4C28(void) {
    s8     tuneA;
    s8     tuneB;
    s8     tuneC;
    Actor* spad;
    Actor* spad2;
    Actor* spad3;
    Actor* spad4;

    spad  = g_SpadWork;
    tuneA = spad->tint.signed_bytes.unk_5D;
    if (tuneA < -0x30) {
        spad->tint.signed_bytes.unk_5D = (s8)(tuneA + 1);
    }
    spad2 = g_SpadWork;
    tuneB = spad2->tint.signed_bytes.unk_5E;
    if (tuneB < -0x30) {
        spad2->tint.signed_bytes.unk_5E = (s8)(tuneB + 1);
        spad2                           = g_SpadWork;
    }
    tuneC = spad2->tint.signed_bytes.unk_5F;
    if (tuneC < -0x30) {
        spad2->tint.signed_bytes.unk_5F = (s8)(tuneC + 1);
    }
    if ((g_SpadWork->tint.word & ~0xFF) == 0xD0D0D000) {
        GFX_FreePaletteFade(g_CurrentActor->unk_93);
        spad3                        = g_SpadWork;
        spad3->flags_00              = (u8)(spad3->flags_00 & 0xDF);
        g_SpadWork->tint.bytes.flags = 0;
        spad4                        = g_SpadWork;
        spad4->tint.bytes.unk_5F     = 0;
        spad4->tint.bytes.unk_5E     = 0;
        spad4->tint.bytes.unk_5D     = 0;
        g_SpadWork->unk_04           = 0;
        return;
    }
    g_CurrentActor->unk_7E = (u16)(g_CurrentActor->unk_7E - 2);
}

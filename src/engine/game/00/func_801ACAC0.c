#include "game_00.h"

MATCH void func_801ACAC0(void) {
    Actor* work_5D;
    Actor* work_5E;
    Actor* work_flags;
    s8     tint_5D;
    s8     tint_5E;
    s8     tint_5F;

    work_5D = g_Task;
    tint_5D = work_5D->tint.signed_bytes.unk_5D;
    if (tint_5D != -0x80) {
        work_5D->tint.signed_bytes.unk_5D = (tint_5D - 4);
    }
    work_5E = g_Task;
    tint_5E = work_5E->tint.signed_bytes.unk_5E;
    if (tint_5E != -0x80) {
        work_5E->tint.signed_bytes.unk_5E = (tint_5E - 4);
    }
    tint_5F = g_Task->tint.signed_bytes.unk_5F;
    if (tint_5F != -0x80) {
        g_Task->tint.signed_bytes.unk_5F = (tint_5F - 4);
    }
    if ((g_Task->tint.word & ~0xFF) == 0x80808000) {
        GFX_FreePaletteFade(g_CurrentActor->unk_93);
        work_flags         = g_Task;
        *(u8*)(work_flags) = (*(u8*)(work_flags) | 0x40);
        g_Task->unk_04     = 0;
        return;
    }
    g_CurrentActor->unk_7E = (g_CurrentActor->unk_7E - 1);
}

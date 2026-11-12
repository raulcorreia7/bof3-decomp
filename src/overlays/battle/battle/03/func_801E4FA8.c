#include "battle_03.h"

MATCH void func_801E4FA8(void) {
    PartyMember* work;

    g_Task->unk_18 = -ONE;
    g_Task->unk_1C = 0;
    func_801DD3CC(g_Task);
    work          = g_Task;
    work->facing  = work->facing ^ 0x2;
    work          = g_Task;
    work->unk_0C  = 0;
    work->unk_10  = 0;
    work->unk_09  = 0x10;
    g_Task->timer = 8;
    func_801E2314(0);
    GFX_AllocPaletteFade(g_Task, -4, -4, -4, 1);
    work               = g_Task;
    work->header.flags = work->header.flags | ACTOR_FLAG_SEMI_TRANSPARENT;
    g_Task->unk_5C     = 2;
    g_Task->unk_5D     = 0;
    g_Task->unk_5E     = 0;
    g_Task->unk_5F     = 0;
    SND_PlayCue(EMI_CUE_ID(SND_BANK_COMMON, 2));
    func_801E30F8();
    work              = g_Task;
    work->header.step = work->header.step + 1;
}

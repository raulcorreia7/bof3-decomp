#include "battle_03.h"

MATCH void func_801E4FA8(void) {
    PartyBattler* work;

    g_SpadWork->unk_18 = -ONE;
    g_SpadWork->unk_1C = 0;
    func_801DD3CC((s32)g_SpadWork);
    work                            = g_SpadWork;
    work->word_08.byte.unk_08       = work->word_08.byte.unk_08 ^ 2;
    work                            = g_SpadWork;
    work->unk_0C                    = 0;
    work->unk_10                    = 0;
    work->word_08.byte.unk_09       = 0x10;
    g_SpadWork->word_08.byte.unk_0A = 8;
    func_801E2314(0);
    GFX_AllocPaletteFade(g_SpadWork, -4, -4, -4, 1);
    work               = g_SpadWork;
    work->flags_00     = work->flags_00 | ACTOR_FLAG_SEMI_TRANSPARENT;
    g_SpadWork->unk_5C = 2;
    g_SpadWork->unk_5D = 0;
    g_SpadWork->unk_5E = 0;
    g_SpadWork->unk_5F = 0;
    SND_PlayCue(EMI_CUE_ID(1, 2));
    func_801E30F8();
    work         = g_SpadWork;
    work->unk_02 = work->unk_02 + 1;
}

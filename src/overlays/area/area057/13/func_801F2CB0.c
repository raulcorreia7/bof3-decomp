#include "area057_13.h"

MATCH void func_801F2CB0(void) {
    PartyBattler* work;
    u8            index;
    s16           y;
    s16           x;
    u8            selection;
    s32           result;

    g_SpadWork = (u8*)g_BattlePartyBattlers;
    index      = D_80144F5A[0];
    y          = g_BattlePartyBattlers[0].unk_30.signed_half;
    x          = g_BattlePartyBattlers[0].unk_2E.signed_half;
    selection  = D_801F4B10[index];
    result     = func_8015CB18(4, 0, selection, x, y);
    if ((u8)result != GAME_NONE) {
        work                      = (PartyBattler*)g_SpadWork;
        work->word_08.byte.unk_0B = (u8)result;
    }
}

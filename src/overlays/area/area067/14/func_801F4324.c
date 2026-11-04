#include "area067_14.h"

MATCH void func_801F4324(void) {
    PartyBattler* work;
    u8            index;
    s16           y;
    s16           x;
    u8            selection;
    s32           result;

    g_SpadWork = (u8*)&g_BattlePartyBattlers[1];
    index      = D_80144F5A[1];
    y          = g_BattlePartyBattlers[1].unk_30.signed_half;
    x          = g_BattlePartyBattlers[1].unk_2E.signed_half;
    selection  = D_801F464C[index];
    result     = func_8015CB18(1, 0, selection, x, y);
    if ((u8)result != GAME_NONE) {
        work                      = (PartyBattler*)g_SpadWork;
        work->word_08.byte.unk_0B = (u8)result;
    }
}

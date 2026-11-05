#include "area067_14.h"

MATCH void func_801F4098(void) {
    u8* work;
    u8  index;
    s16 y;
    s16 x;
    u8  selection;
    s32 result;

    g_SpadWork = (u8*)&g_BattlePartyBattlers[2];
    index      = D_80144F5A[2];
    y          = g_BattlePartyBattlers[2].unk_30.signed_half;
    x          = g_BattlePartyBattlers[2].unk_2E.signed_half;
    selection  = D_801F4644[index];
    result     = func_8015CC00(3, 0, selection, x, y, g_BattlePartyBattlers[2].word_3C.word);
    if ((u8)result != GAME_NONE) {
        work      = SP_REF(u8*, 0x44u);
        work[0xB] = result;
    }
}

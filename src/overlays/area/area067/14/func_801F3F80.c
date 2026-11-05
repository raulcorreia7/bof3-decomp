#include "area067_14.h"

MATCH void func_801F3F80(void) {
    u8* work;
    u8  index;
    s32 y;
    s32 x;
    u8  selection;
    s32 result;

    g_Task    = (u8*)&g_BattlePartyBattlers[0];
    index     = D_80144F5A[0];
    y         = g_BattlePartyBattlers[0].coord_y_38.raw;
    x         = g_BattlePartyBattlers[0].coord_x_34.raw;
    selection = D_801F4644[index];
    result    = func_8015CC00(3, 0, selection, x, y, g_BattlePartyBattlers[0].word_3C.word);
    if ((u8)result != GAME_NONE) {
        work      = SP_REF(u8*, 0x44u);
        work[0xB] = (u8)result;
    }
}

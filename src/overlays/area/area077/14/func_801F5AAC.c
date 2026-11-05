#include "area077_14.h"

MATCH void func_801F5AAC(void) {
    u8  index;
    s16 y;
    s16 x;
    u8  selection;
    s32 result;
    u8* work;

    SP_REF(u8*, 0x44u) = (u8*)g_BattlePartyBattlers;
    index              = D_80144F5A[0];
    y                  = g_BattlePartyBattlers[0].unk_30.signed_half;
    x                  = g_BattlePartyBattlers[0].unk_2E.signed_half;
    selection          = D_801F6B28[index];
    result             = func_8015CB18(3, 0, selection, x, y);
    if ((u8)result != GAME_NONE) {
        work      = (u8*)g_Task;
        work[0xB] = (s8)result;
    }
}

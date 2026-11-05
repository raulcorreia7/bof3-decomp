#include "area077_14.h"

MATCH void func_801F5D00(void) {
    u8  index;
    s16 y;
    s16 x;
    u8  selection;
    s32 result;
    u8* work;

    TASK_SET((u8*)&g_BattlePartyBattlers[2]);
    index     = D_80144F5A[2];
    y         = g_BattlePartyBattlers[2].unk_30.signed_half;
    x         = g_BattlePartyBattlers[2].unk_2E.signed_half;
    selection = D_801F6B48[index];
    result    = func_8015CB18(3, 0, selection, x, y);
    if ((u8)result != GAME_NONE) {
        work      = (u8*)g_Task;
        work[0xB] = (s8)result;
    }
}

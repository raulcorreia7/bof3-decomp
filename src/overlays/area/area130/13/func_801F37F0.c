#include "area130_13.h"

MATCH void func_801F37F0(void) {
    u8* work;
    u8  index;
    s16 y;
    s16 x;
    u8  selection;
    s32 result;

    TASK_SET((u8*)&g_BattlePartyBattlers[1]);
    index     = D_80144F5A[1];
    y         = g_BattlePartyBattlers[1].unk_30.signed_half;
    x         = g_BattlePartyBattlers[1].unk_2E.signed_half;
    selection = (D_801F3ED8 + 0x28u)[index];
    result    = func_8015CB18(3, 0, selection, x, y);
    if ((u8)result != GAME_NONE) {
        work       = (u8*)g_Task;
        work[0x0B] = (s8)result;
    }
}

#include "area134_13.h"

MATCH void func_801F5114(void) {
    u8* work;
    u8  index;
    s16 y;
    s16 x;
    u8  selection;
    s32 result;

    TASK_SET((u8*)g_BattlePartyBattlers);
    index     = D_80144F5A[0];
    y         = g_BattlePartyBattlers[0].unk_30.signed_half;
    x         = g_BattlePartyBattlers[0].unk_2E.signed_half;
    selection = D_801F5724[0x150u + index];
    result    = func_8015CB18(4, 0, selection, x, y);
    if ((u8)result != 0xFF) {
        work      = (u8*)g_Task;
        work[0xB] = (u8)result;
    }
}

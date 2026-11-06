#include "area094_13.h"

MATCH void func_801F3050(void) {
    u8  index;
    s16 y;
    s16 x;
    u8  selection;
    s32 result;
    u8* work;

    TASK_SET((u8*)g_BattlePartyBattlers);
    index     = g_PartyFieldOrder[0];
    y         = g_BattlePartyBattlers[0].unk_30.signed_half;
    x         = g_BattlePartyBattlers[0].unk_2E.signed_half;
    selection = (D_801F3504 + 8)[index];
    result    = func_8015CB18(4, 0, selection, x, y);
    if ((u8)result != GAME_NONE) {
        work      = (u8*)g_Task;
        work[0xB] = result;
    }
}

#include "area136_13.h"

MATCH void func_801F2ED0(void) {
    u8* work;
    u8  index;
    s16 y;
    s16 x;
    u8  selection;
    s32 result;

    TASK_SET((u8*)&g_BattlePartyBattlers[2]);
    index     = *(u8*)(PARTY_FIELD_ORDER_BASE + 2);
    y         = g_BattlePartyBattlers[2].unk_30.signed_half;
    x         = g_BattlePartyBattlers[2].unk_2E.signed_half;
    selection = D_801F3424[index];
    result    = func_8015CB18(2, 0, selection, x, y);
    if ((u8)result != 0xFF) {
        work      = g_Task;
        work[0xB] = result;
    }
}

#include "area133_13.h"

MATCH void func_801F2CEC(void) {
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
    selection = D_801F2DD4[index];
    result    = func_8015CB18(3, 0, selection, x, y);
    if ((u8)result != 0xFF) {
        work      = TASK_BYTES;
        work[0xB] = (u8)result;
    }
}

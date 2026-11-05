#include "area117_13.h"

MATCH void func_801F3EF0(void) {
    u8* work;
    u8  index;
    s16 y;
    s16 x;
    u8  selection;
    s32 result;

    SP_REF(u8*, 0x44u) = (u8*)&g_BattlePartyBattlers[2];
    index              = D_80144F5A[2];
    y                  = g_BattlePartyBattlers[2].unk_30.signed_half;
    x                  = g_BattlePartyBattlers[2].unk_2E.signed_half;
    selection          = (D_801F4624 + 0x54u)[index];
    result             = func_8015CB18(2, 0, selection, x, y);
    if ((u8)result != GAME_NONE) {
        work       = (u8*)g_Task;
        work[0x0B] = (s8)result;
    }
}

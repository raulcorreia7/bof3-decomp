#include "area136_13.h"

MATCH void func_801F2F50(void) {
    u8* work;
    u8  index;
    s16 y;
    s16 x;
    u8  selection;
    s32 result;

    SP_REF(u8*, 0x44u) = (u8*)&g_BattlePartyBattlers[1];
    index              = *(u8*)(PARTY_ORDER_WALKING + 1);
    y                  = g_BattlePartyBattlers[1].unk_30.signed_half;
    x                  = g_BattlePartyBattlers[1].unk_2E.signed_half;
    selection          = D_801F3424[0xCu + index];
    result             = func_8015CB18(1, 0, selection, x, y);
    if ((u8)result != 0xFF) {
        work      = g_Task;
        work[0xB] = (u8)result;
    }
}

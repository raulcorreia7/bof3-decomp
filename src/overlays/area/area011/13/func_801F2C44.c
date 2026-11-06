#include "area011_13.h"

MATCH void func_801F2C44(void) {
    u8* work;
    u8  index;
    s16 y;
    s16 x;
    u8  selection;
    s32 result;

    TASK_SET(g_BattlePartyBattlers);
    index     = g_PartyWalkOrder[2];
    y         = g_BattlePartyBattlers[0].unk_30.signed_half;
    x         = g_BattlePartyBattlers[0].unk_2E.signed_half;
    selection = D_801F2D78[index];
    result    = func_8015CB18(1, 0, selection, x, y);
    if ((u8)result != GAME_NONE) {
        work      = TASK_BYTES;
        work[0xB] = result;
    }
}

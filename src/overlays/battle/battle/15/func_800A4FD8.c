#include "battle_15.h"

/* Four-byte battle slot rows: the gate byte at +0x03 skips the row, the three
 * slot bytes at +0x00..+0x02 index the D_800B4C7C value table. */

MATCH s32 func_800A4FD8(void) {
    s32 row_index;
    u32 sum;
    u8  slot_01;
    u8  slot_02;

    row_index = g_BattleTargetCursorCol + D_801485CA;
    if (g_BattleTargetRows[row_index].gate_03 == GAME_NONE) {
        return 0;
    }
    sum     = D_800B4C7C[g_BattleTargetRows[row_index].slot_00];
    slot_01 = g_BattleTargetRows[row_index].slot_01;
    if (slot_01 != GAME_NONE) {
        sum += D_800B4C7C[slot_01];
    }
    slot_02 = g_BattleTargetRows[row_index].slot_02;
    if (slot_02 != GAME_NONE) {
        sum += D_800B4C7C[slot_02];
    }
    return g_Game.members[g_BattleMessageSlot[5]].chr.ap >= (sum & BYTE_MASK);
}

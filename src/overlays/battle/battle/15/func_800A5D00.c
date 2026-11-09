#include "battle_15.h"

/* Four-byte battle slot rows. */

MATCH bool func_800A5D00(void) {
    s32 row_index;
    u32 sum;
    u8  slot_01;
    u8  slot_02;

    /* battle_15.h types the pair as volatile u16. */
    row_index = *(s16*)&D_801485EC + *(s16*)&D_801485EE;
    if (D_80145518[row_index].gate_03 == GAME_NONE) {
        return 0;
    }
    sum     = D_800B4C7C[D_80145518[row_index].slot_00];
    slot_01 = D_80145518[row_index].slot_01;
    if (slot_01 != GAME_NONE) {
        sum += D_800B4C7C[slot_01];
    }
    slot_02 = D_80145518[row_index].slot_02;
    if (slot_02 != GAME_NONE) {
        sum += D_800B4C7C[slot_02];
    }
    return g_Game.members[g_BattleMessageSlot[5]].chr.ap >= (sum & BYTE_MASK);
}

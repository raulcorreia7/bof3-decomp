#include "battle_15.h"

/* func_800AE260 */
MATCH void Battle_AllocActionEffect(u16 selection, u32 payload) {
    u8* row;
    u32 slot;

    g_Battle.action_id                   = selection;
    row                                  = D_800B6AB0[(selection >> 8) & BYTE_MASK];
    slot                                 = Battle_AllocEffect(2, row[selection & BYTE_MASK]) & BYTE_MASK;
    g_BattleEffects[slot].target.address = payload;
}

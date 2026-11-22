#include "battle_15.h"

/* func_800AE260 */
MATCH void Battle_AllocActionEffect(u16 selection, u32 payload) {
    u8* steps;
    u32 slot;

    g_Battle.action_id                   = selection;
    steps                                = D_800B6AB0[(selection >> 8) & BYTE_MASK];
    slot                                 = Battle_AllocEffect(2, steps[selection & BYTE_MASK]) & BYTE_MASK;
    g_BattleEffects[slot].target.address = payload;
}

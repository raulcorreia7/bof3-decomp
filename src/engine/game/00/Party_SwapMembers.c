#include "game_00.h"

/* The battler rows embed the character record as `chr`; byte 0x79 indexes g_CharSlot and `character_index` stores
 * the mapped record id. */
MATCH void Party_SwapMembers(u32 slot_a, u32 slot_b, u32 skip_state) {
    Party_SwapBattlerRows(slot_a & BYTE_MASK, slot_b & BYTE_MASK, skip_state & BYTE_MASK);

    g_GameState = &g_BattlePartyBattlers[slot_a & BYTE_MASK];
    TASK_SET(g_GameState);
    func_801C1254(g_GameState->chr.character_id, slot_a & BYTE_MASK);
    g_GameState->chr             = g_Characters[g_CharSlot[g_GameState->chr.character_id]];
    g_GameState->character_index = g_CharSlot[g_GameState->chr.character_id];

    g_GameState = &g_BattlePartyBattlers[slot_b & BYTE_MASK];
    TASK_SET(g_GameState);
    func_801C1254(g_GameState->chr.character_id, slot_b & BYTE_MASK);
    g_GameState->chr             = g_Characters[g_CharSlot[g_GameState->chr.character_id]];
    g_GameState->character_index = g_CharSlot[g_GameState->chr.character_id];
}

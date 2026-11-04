#include "game_00.h"

/* The 0x80145E90 rows are shared PartyBattler records. Their layout exposes
 * selected cells at 0x74..0x117, not an embedded Character, although
 * this function copies the full 0xA4-byte character record there. Byte 0x79
 * indexes g_CharSlot; byte 0x13C stores the mapped record id.
 */
MATCH void Party_SwapMembers(u32 slot_a, u32 slot_b, u32 skip_state) {
    Party_SwapBattlerRows(slot_a & BYTE_MASK, slot_b & BYTE_MASK, skip_state & BYTE_MASK);

    g_GameState = (GameStateRecord*)((u8*)g_BattlePartyBattlers + (slot_a & BYTE_MASK) * BATTLE_PARTY_STRIDE);
    g_SpadWork  = (Actor*)g_GameState;
    func_801C1254(g_GameState->slot_index_79, slot_a & BYTE_MASK);
    *(Character*)(((u8*)g_GameState) + 0x74) = g_Characters[g_CharSlot[g_GameState->slot_index_79]];
    g_GameState->slot_13C                    = g_CharSlot[g_GameState->slot_index_79];

    g_GameState = (GameStateRecord*)((u8*)g_BattlePartyBattlers + (slot_b & BYTE_MASK) * BATTLE_PARTY_STRIDE);
    g_SpadWork  = (Actor*)g_GameState;
    func_801C1254(g_GameState->slot_index_79, slot_b & BYTE_MASK);
    *(Character*)(((u8*)g_GameState) + 0x74) = g_Characters[g_CharSlot[g_GameState->slot_index_79]];
    g_GameState->slot_13C                    = g_CharSlot[g_GameState->slot_index_79];
}

#include "engine/game/00/game_00.h"

/* The battler rows embed the character record as `chr`; byte 0x79 indexes g_CharSlot and `character_index` stores
 * the mapped record id. */
MATCH void Party_MemberSwap(u32 slot_a, u32 slot_b, u32 skip_state) {
    Party_BattlersSwapRows(slot_a & BYTE_MASK, slot_b & BYTE_MASK, skip_state & BYTE_MASK);

    g_GameState = &g_Game.members[slot_a & BYTE_MASK];
    SELF_SET(g_GameState);
    Party_MemberLoadSprite(g_GameState->chr.character_id, slot_a & BYTE_MASK);
    g_GameState->chr             = g_Characters[g_CharSlot[g_GameState->chr.character_id]];
    g_GameState->character_index = g_CharSlot[g_GameState->chr.character_id];

    g_GameState = &g_Game.members[slot_b & BYTE_MASK];
    SELF_SET(g_GameState);
    Party_MemberLoadSprite(g_GameState->chr.character_id, slot_b & BYTE_MASK);
    g_GameState->chr             = g_Characters[g_CharSlot[g_GameState->chr.character_id]];
    g_GameState->character_index = g_CharSlot[g_GameState->chr.character_id];
}

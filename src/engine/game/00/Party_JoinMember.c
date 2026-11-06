#include "game_00.h"

MATCH s32 Party_JoinMember(s32 char_id) {
    s32 id;

    func_801C1840();
    id = char_id & 0xFF;
    /* FAKE: retail reads g_CharSlot as u8[]. */
    g_Characters[((u8*)g_CharSlot)[id]].unk_07 |= 1;
    if (g_PartySize < PARTY_SLOT_COUNT) {
        D_80144F5A[g_PartySize]                         = char_id;
        D_80144F5D[g_PartySize]                         = char_id;
        g_BattlePartyBattlers[g_PartySize].header.flags = PARTY_BATTLER_FLAG_OCCUPIED;
        Party_ClearBattlerState(g_PartySize);
        TASK_SET(&g_BattlePartyBattlers[g_PartySize]);
        g_Task->active_flags = 1;
        func_801C1254(id, g_PartySize);
        /* FAKE: retail reads g_CharSlot as u8[]. */
        *((Character*)((u8*)&g_BattlePartyBattlers[g_PartySize] + 0x74)) = g_Characters[((u8*)g_CharSlot)[id]];
        g_Task->unk_05                                                   = g_PartySize;
        g_Task->unk_4B                                                   = 0xFF;
        /* FAKE: retail reads g_CharSlot as u8[]. */
        g_BattlePartyBattlers[g_PartySize].character_index               = ((u8*)g_CharSlot)[char_id & 0xFF];
        /* FAKE: retail keeps the incremented party count in v0. */
        ORDER_LOCK(g_PartySize += 1);
        return 0;
    }
    g_GameStateIndex = GAME_REQUEST_SHOP;
    return 1;
}

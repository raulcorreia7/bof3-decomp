#include "game_00.h"

MATCH s32 Party_JoinMember(s32 char_id) {
    s32 id;

    func_801C1840();
    id = char_id & BYTE_MASK;
    /* FAKE: retail reads g_CharSlot as u8[]. */
    g_Characters[((u8*)g_CharSlot)[id]].unk_07 |= 1;
    if (g_PartySize < PARTY_SLOT_COUNT) {
        D_80144F5A[g_PartySize]                     = (u8)char_id;
        D_80144F5D[g_PartySize]                     = (u8)char_id;
        g_BattlePartyBattlers[g_PartySize].flags_00 = PARTY_BATTLER_FLAG_OCCUPIED;
        Party_ClearBattlerState(g_PartySize);
        g_SpadWork           = (Actor*)&g_BattlePartyBattlers[g_PartySize];
        g_SpadWork->flags_24 = 1;
        func_801C1254(id, g_PartySize);
        /* FAKE: retail reads g_CharSlot as u8[]. */
        *((Character*)((u8*)&g_BattlePartyBattlers[g_PartySize] + 0x74)) = g_Characters[((u8*)g_CharSlot)[id]];
        g_SpadWork->unk_05                                               = g_PartySize;
        g_SpadWork->unk_4B                                               = 0xFF;
        /* FAKE: retail reads g_CharSlot as u8[]. */
        D_80145FCC[g_PartySize * BATTLE_PARTY_STRIDE]                    = ((u8*)g_CharSlot)[char_id & BYTE_MASK];
        /* FAKE: retail keeps the incremented party count in v0. */
        ORDER_LOCK(g_PartySize += 1);
        return 0;
    }
    g_GameStateIndex = GAME_REQUEST_SHOP;
    return 1;
}

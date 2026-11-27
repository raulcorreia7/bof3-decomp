#include "engine/game/00/game_00.h"

MATCH s32 Party_MemberJoin(s32 char_id) {
    s32 id;

    func_801C1840();
    id = char_id & BYTE_MASK;
    /* FAKE: retail reads g_CharSlot as u8[]. */
    g_Characters[((u8*)g_CharSlot)[id]].party_flags |= PARTY_FLAG_JOINED;
    if (g_PartySize < PARTY_SLOT_COUNT) {
        g_PartyFieldOrder[g_PartySize]           = char_id;
        g_PartyBattleOrder[g_PartySize]          = char_id;
        g_Game.members[g_PartySize].header.flags = PARTY_MEMBER_FLAG_OCCUPIED;
        Party_BattlersClearState(g_PartySize);
        SELF_SET(&g_Game.members[g_PartySize]);
        SELF(Actor)->active_flags = 1;
        Party_MemberLoadSprite(id, g_Game.party_size);
        /* FAKE: retail reads g_CharSlot as u8[]. */
        g_Game.members[g_Game.party_size].chr             = g_Characters[((u8*)g_CharSlot)[id]];
        SELF(Actor)->unk_05                               = g_PartySize;
        SELF(Actor)->script_record                        = 0xFF;
        /* FAKE: retail reads g_CharSlot as u8[]. */
        g_Game.members[g_Game.party_size].character_index = ((u8*)g_CharSlot)[char_id & BYTE_MASK];
        /* FAKE: retail keeps the incremented party count in v0. */
        do {
            g_PartySize += 1;
        } while (0);
        return 0;
    }
    g_GameStateIndex = GAME_REQUEST_SHOP;
    return 1;
}

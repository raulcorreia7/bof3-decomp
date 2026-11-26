#include "engine/game/00/game_00.h"

/* func_801C1ABC */
/* Takes a character out of both party orders, closes the gap in the member records and drops the formation it no longer fits. */
MATCH void Party_MemberRemove(s32 character_id) {
    s32 slot;

    func_801C1840();
    slot = 0;
    while (slot < g_PartySize && g_PartyBattleOrder[slot] != (u8)character_id) {
        slot++;
    }
    g_PartyBattleOrder[slot] = 0xFF;
    for (; slot < g_PartySize - 1; slot++) {
        if (g_PartyBattleOrder[slot] == 0xFF) {
            g_PartyBattleOrder[slot]     = g_PartyBattleOrder[slot + 1];
            g_PartyBattleOrder[slot + 1] = 0xFF;
        }
    }
    slot = 0;
    while (slot < g_PartySize && g_PartyFieldOrder[slot] != (u8)character_id) {
        slot++;
    }
    g_PartyFieldOrder[slot] = 0xFF;
    for (slot = 0; slot < g_PartySize - 1; slot++) {
        if (g_PartyFieldOrder[slot] == 0xFF) {
            SELF_SET(&g_Game.members[slot]);
            g_PartyFieldOrder[slot]              = g_PartyFieldOrder[slot + 1];
            g_PartyFieldOrder[slot + 1]          = 0xFF;
            g_Game.members[slot]                 = g_Game.members[slot + 1];
            SELF(Actor)->unk_05                  = slot;
            SELF(Actor)->sheet_row               = slot * 0x50;
            SELF(Actor)->clut_select             = slot + 0x78;
            SELF(Actor)->script_record           = 0xFF;
            g_Game.members[slot].character_index = g_CharSlot[g_Game.members[slot].chr.character_id];
        }
    }
    g_Game.members[g_PartySize - 1].header.flags = 0;
    Party_BattlersClearState((g_PartySize - 1) & BYTE_MASK);
    if (g_PartySize == 3) {
        u8* formation = &g_PartyFormation;

        if (*formation >= 3) {
            *formation = 0;
            goto done;
        }
    }
    if (g_PartySize == 2) {
        g_PartyFormation = 0;
    }
done:
    g_PartySize = g_PartySize - 1;
}

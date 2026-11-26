#include "engine/game/00/game_00.h"

MATCH void Party_BattlersBuild(u32 order) {
    s32          i;
    u8           type;
    u8*          entry_table;
    Character*   record_base;
    PartyMember* battler;
    if (g_GameStateIndex != GAME_REQUEST_SHOP) {
        Party_BattlersReset();
    }
    for (i = 0; i < g_Game.party_size; i++) {
        battler        = &g_BattlePartyBattlers[i];
        g_Game.current = battler;
        TASK_SET(battler);
        battler->header.flags = PARTY_MEMBER_FLAG_OCCUPIED;
        entry_table           = g_PartyFieldOrder;
        TASK(Actor)->unk_05   = i;
        ((void (*)(u8, u8))Party_MemberLoadSprite)(*((entry_table + ((order & BYTE_MASK) * 3)) + i), i);
        TASK(Actor)->unk_48               = 0;
        TASK(Actor)->scale.x              = 65536;
        TASK(Actor)->scale.y              = 65536;
        type                              = g_CharSlot[*((entry_table + ((order & BYTE_MASK) * 3)) + i)];
        g_Game.members[i].character_index = type;
        /* g_Characters is the 0xA4-byte character-record table; g_PartyFieldOrder is at +0x5F2. */
        record_base                       = (Character*)(g_PartyFieldOrder - 0x5F2);
        g_BattlePartyBattlers[i].chr      = record_base[type];
        g_BattlePartyBattlers[i].status.field.flags.unsigned_value &= 0xFE;
        if ((order & BYTE_MASK) != 0) {
            if ((g_Characters[g_Game.members[i].character_index].status & STATUS_POISONED) != 0) {
                GFX_PaletteAllocFade(TASK(void), -4, -8, 0, 0);
            }
        } else {
            func_801C3204();
        }
    }
}

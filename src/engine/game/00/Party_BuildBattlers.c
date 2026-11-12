#include "game_00.h"

MATCH void Party_BuildBattlers(u32 mode) {
    s32          i;
    u8           kind;
    u8*          entry_table;
    Character*   record_base;
    PartyMember* battler;
    if (g_GameStateIndex != GAME_REQUEST_SHOP) {
        Party_ResetBattlers();
    }
    for (i = 0; i < g_Game.party_size; i++) {
        battler        = &g_BattlePartyBattlers[i];
        g_Game.current = battler;
        TASK_SET(battler);
        battler->header.flags = PARTY_MEMBER_FLAG_OCCUPIED;
        entry_table           = g_PartyFieldOrder;
        g_Task->unk_05        = i;
        ((void (*)(u8, u8))Party_LoadMemberSprite)(*((entry_table + ((mode & BYTE_MASK) * 3)) + i), i);
        g_Task->unk_48                    = 0;
        g_Task->scale.x                   = 65536;
        g_Task->scale.y                   = 65536;
        kind                              = g_CharSlot[*((entry_table + ((mode & BYTE_MASK) * 3)) + i)];
        g_Game.members[i].character_index = kind;
        /* g_Characters is the 0xA4-byte character-record table; g_PartyFieldOrder is at +0x5F2. */
        record_base                       = (Character*)(g_PartyFieldOrder - 0x5F2);
        g_BattlePartyBattlers[i].chr      = record_base[kind];
        g_BattlePartyBattlers[i].status.field.flags_12C.u8_value &= 0xFE;
        if ((mode & BYTE_MASK) != 0) {
            if ((g_Characters[g_Game.members[i].character_index].status & STATUS_POISONED) != 0) {
                GFX_AllocPaletteFade((void*)g_Task, -4, -8, 0, 0);
            }
        } else {
            func_801C3204();
        }
    }
}

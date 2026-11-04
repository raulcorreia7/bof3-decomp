#include "game_00.h"

MATCH void Party_BuildBattlers(u32 mode) {
    s32        i;
    u8         kind;
    s32        slot_offset;
    u8*        entry_table;
    Character* record_base;
    if (g_GameStateIndex != GAME_REQUEST_SHOP) {
        Party_ResetBattlers();
    }
    for (i = 0; i < g_PartySize; i++) {
        g_GameState = (GameStateRecord*)(((u8*)g_BattlePartyBattlers) + (i * BATTLE_PARTY_STRIDE));
        g_SpadWork  = (Actor*)(((u8*)g_BattlePartyBattlers) + (i * BATTLE_PARTY_STRIDE));
        *(((u8*)g_BattlePartyBattlers) + (i * 0x140)) = 1;
        entry_table                                   = D_80144F5A;
        g_SpadWork->unk_05                            = i;
        ((void (*)(u8, u8))func_801C1254)(*((entry_table + ((mode & BYTE_MASK) * 3)) + i), i);
        *((u8*)(((u8*)g_SpadWork) + 0x48))  = 0;
        *((u32*)(((u8*)g_SpadWork) + 0x40)) = 0x10000;
        *((u32*)(((u8*)g_SpadWork) + 0x44)) = 0x10000;
        kind                                = g_CharSlot[*((entry_table + ((mode & BYTE_MASK) * 3)) + i)];
        D_80145FCC[i * BATTLE_PARTY_STRIDE] = kind;
        slot_offset                         = i * BATTLE_PARTY_STRIDE;
        /* g_Characters is the 0xA4-byte character-record table; D_80144F5A is at +0x5F2. */
        record_base                         = (Character*)(((u8*)D_80144F5A) - 0x5F2);
        *((Character*)((((u8*)g_BattlePartyBattlers) + 0x74) + slot_offset)) = record_base[kind];
        *((((u8*)g_BattlePartyBattlers) + 0x12C) + slot_offset) &= 0xFE;
        if ((mode & BYTE_MASK) != 0) {
            if ((g_Characters[D_80145FCC[slot_offset]].status & STATUS_POISONED) != 0) {
                GFX_AllocPaletteFade((void*)g_SpadWork, -4, -8, 0, 0);
            }
        } else {
            func_801C3204();
        }
    }
}

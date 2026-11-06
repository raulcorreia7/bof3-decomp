#include "game_00.h"

MATCH void Party_BuildBattlers(u32 mode) {
    s32           i;
    u8            kind;
    u8*           entry_table;
    Character*    record_base;
    PartyBattler* battler;
    if (g_GameStateIndex != GAME_REQUEST_SHOP) {
        Party_ResetBattlers();
    }
    for (i = 0; i < g_PartySize; i++) {
        battler     = &g_BattlePartyBattlers[i];
        g_GameState = (GameState*)battler;
        TASK_SET(battler);
        battler->flags = PARTY_BATTLER_FLAG_OCCUPIED;
        entry_table    = D_80144F5A;
        g_Task->unk_05 = i;
        ((void (*)(u8, u8))func_801C1254)(*((entry_table + ((mode & BYTE_MASK) * 3)) + i), i);
        g_Task->unk_48                       = 0;
        g_Task->unk_40                       = 0x10000;
        g_Task->unk_44                       = 0x10000;
        kind                                 = g_CharSlot[*((entry_table + ((mode & BYTE_MASK) * 3)) + i)];
        g_BattlePartyBattlers[i].record_slot = kind;
        /* g_Characters is the 0xA4-byte character-record table; D_80144F5A is at +0x5F2. */
        record_base                          = (Character*)(D_80144F5A - 0x5F2);
        g_BattlePartyBattlers[i].chr         = record_base[kind];
        g_BattlePartyBattlers[i].unk_12C[0] &= 0xFE;
        if ((mode & BYTE_MASK) != 0) {
            if ((g_Characters[g_BattlePartyBattlers[i].record_slot].status & STATUS_POISONED) != 0) {
                GFX_AllocPaletteFade((void*)g_Task, -4, -8, 0, 0);
            }
        } else {
            func_801C3204();
        }
    }
}

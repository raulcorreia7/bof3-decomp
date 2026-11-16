#include "battle_15.h"

/* Ends the battle selection: hands the chosen slot to the sound request, clears it, then copies the battler
 * work rows and resets the effect slots. */
#ifdef NON_MATCHING
NON_MATCHING bool func_8009AC18(void) {
    u8* slots[6];
    u8* base;
    u8* row;
    u8* cell;
    u8* count;
    u8  character_index;
    u32 i;
    u32 row_offset;
    base     = (u8*)&g_Characters[g_CharSlot[g_PartyBattleOrder[D_801485C4]]];
    slots[0] = base + 0xE;
    slots[1] = base + 0xF;
    slots[2] = base + 0x10;
    slots[3] = base + 0x11;
    slots[4] = base + 0x12;
    slots[5] = base + 0x13;
    if ((*slots[g_BattleItemRow] == 0) || (g_BattleItemRow == 0)) {
        return 0;
    }
    Item_Add(D_800B44B8[g_BattleItemRow], *slots[g_BattleItemRow], 1, 0);
    *slots[g_BattleItemRow] = 0;
    Char_RebuildStats((Character*)base);
    count = &g_BattlePartyCount;
    if (*count != 0) {
        i = 0;
        do {
            row_offset      = (u8)i * BATTLE_PARTY_STRIDE;
            row             = (u8*)D_80145F04 + row_offset;
            character_index = D_80145F04[row_offset + 0xC8];
            cell            = (u8*)&g_Characters[character_index];
            row[0x0E]       = cell[0x0E];
            row[0x0F]       = cell[0x0F];
            row[0x10]       = cell[0x10];
            row[0x11]       = cell[0x11];
            row[0x12]       = cell[0x12];
            row[0x13]       = cell[0x13];
            memcpy(row + 0x3C, cell + 0x1C, 0x20);
            i++;
        } while ((u8)i < *count);
    }
    Battle_ApplyFormationStats();
    i = 0;
    do {
        row_offset = (u8)i * BATTLE_PARTY_STRIDE;
        row        = D_80145F20 + row_offset;
        if (ACTOR_IN_USE(g_Game.members[(u8)i])) {
            memcpy(row, row + 0x20, 0x20);
        }
        i++;
    } while ((u8)i < 3);
    i = 0;
    func_800A4458();
    if (*count != 0) {
        do {
            Battle_RescaleStats(i);
            i++;
        } while ((u8)i < *count);
    }
    return 1;
}
#else
INCLUDE_ASM(func_8009AC18);
#endif

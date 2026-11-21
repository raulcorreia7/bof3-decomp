#include "battle_15.h"

/* Ends the battle selection: hands the chosen slot to the sound request, clears it, then copies the battler
 * work rows and resets the effect slots. */
/* func_8009AC18 */
MATCH bool Battle_Unequip(void) {
    u8* slots[6];
    u8* row;
    u8* cell;
    u8  character_index;
    u32 i;
    u32 row_offset;
    u32 row_index;
    row      = (u8*)&g_Characters[g_CharSlot[g_PartyBattleOrder[D_801485C4]]];
    slots[0] = row + 0xE;
    slots[1] = row + 0xF;
    slots[2] = row + 0x10;
    slots[3] = row + 0x11;
    slots[4] = row + 0x12;
    slots[5] = row + 0x13;
    if ((*slots[g_BattleItemRow] == 0) || (g_BattleItemRow == 0)) {
        return 0;
    }
    Item_Add(D_800B44B8[g_BattleItemRow], *slots[g_BattleItemRow], 1, 0);
    *slots[g_BattleItemRow] = 0;
    Char_RebuildStats((Character*)row);
    {
        u8* count = &g_BattlePartyCount;

        i = 0;
        if (*count != 0) {
            do {
                row_index  = (u8)i;
                row_offset = row_index << 2;
                row_offset += row_index;
                row_offset <<= 6;
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
    }
    Battle_ApplyFormationStats();
    {
        u8* dst_base = D_80145F20;
        u8* src_base = dst_base + 0x20;

        i = 0;
        do {
            row_offset = (u8)i * BATTLE_PARTY_STRIDE;
            if (ACTOR_IN_USE(g_Game.members[(u8)i])) {
                memcpy((u8*)(row_offset + (u32)dst_base), (u8*)(row_offset + (u32)src_base), 0x20);
            }
            i++;
        } while ((u8)i < 3);
    }
    i = 0;
    func_800A4458();
    if (g_BattlePartyCount != 0) {
        do {
            Battle_RescaleStats((u8)i);
            i++;
        } while ((u8)i < g_BattlePartyCount);
    }
    return 1;
}

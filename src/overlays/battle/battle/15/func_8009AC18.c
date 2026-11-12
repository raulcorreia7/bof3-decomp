#include "battle_15.h"

extern u8 D_80145F20[];

/* Ends the battle selection: hands the chosen slot to the sound request, clears it, then copies the battler
 * work rows and resets the effect slots. */
#ifdef NON_MATCHING
NON_MATCHING bool func_8009AC18(void) {
    u8* slots[6];
    u8* base;
    u8* row;
    u8* cell;
    u32 i;
    s32 j;

    base     = &g_Characters[g_CharSlot[g_PartyBattleOrder[D_801485C4]]];
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
    Char_RebuildStats(base);
    if (g_Battle.party_count != 0) {
        i = 0;
        do {
            cell                   = &g_Characters[g_Game.members[i].character_index];
            row                    = D_80145F04 + i * BATTLE_PARTY_STRIDE;
            FIELD(u8, row, 0xEu)   = FIELD(u8, cell, 0xEu);
            FIELD(u8, row, 0xFu)   = FIELD(u8, cell, 0xFu);
            FIELD(u8, row, 0x10u)  = FIELD(u8, cell, 0x10u);
            FIELD(u8, row, 0x11u)  = FIELD(u8, cell, 0x11u);
            FIELD(u8, row, 0x12u)  = FIELD(u8, cell, 0x12u);
            FIELD(u8, row, 0x13u)  = FIELD(u8, cell, 0x13u);
            FIELD(s32, row, 0x3Cu) = FIELD(s32, cell, 0x1Cu);
            FIELD(s32, row, 0x40u) = FIELD(s32, cell, 0x20u);
            FIELD(s32, row, 0x44u) = FIELD(s32, cell, 0x24u);
            FIELD(s32, row, 0x48u) = FIELD(s32, cell, 0x28u);
            FIELD(s32, row, 0x4Cu) = FIELD(s32, cell, 0x2Cu);
            FIELD(s32, row, 0x50u) = FIELD(s32, cell, 0x30u);
            FIELD(s32, row, 0x54u) = FIELD(s32, cell, 0x34u);
            FIELD(s32, row, 0x58u) = FIELD(s32, cell, 0x38u);
            i++;
        } while ((u8)i < g_Battle.party_count);
    }
    Battle_ApplyFormationStats();
    j = 0;
    do {
        row = D_80145F20 + j * BATTLE_PARTY_STRIDE;
        if (ACTOR_IN_USE(g_Game.members[j])) {
            cell                   = row + 0x20;
            FIELD(s32, row, 0x0u)  = FIELD(s32, cell, 0x0u);
            FIELD(s32, row, 0x4u)  = FIELD(s32, cell, 0x4u);
            FIELD(s32, row, 0x8u)  = FIELD(s32, cell, 0x8u);
            FIELD(s32, row, 0xCu)  = FIELD(s32, cell, 0xCu);
            FIELD(s32, row, 0x10u) = FIELD(s32, cell, 0x10u);
            FIELD(s32, row, 0x14u) = FIELD(s32, cell, 0x14u);
            FIELD(s32, row, 0x18u) = FIELD(s32, cell, 0x18u);
            FIELD(s32, row, 0x1Cu) = FIELD(s32, cell, 0x1Cu);
        }
        j++;
    } while ((u32)j < 3);
    func_800A4458();
    if (g_Battle.party_count != 0) {
        i = 0;
        do {
            Battle_RescaleStats(i);
            i++;
        } while ((u8)i < g_Battle.party_count);
    }
    return 1;
}
#else
INCLUDE_ASM(func_8009AC18);
#endif

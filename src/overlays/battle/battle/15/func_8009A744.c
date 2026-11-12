#include "battle_15.h"

extern u8 D_80145F20[];

/* Applies the battle selection: hands the six chosen slots to the sound queue, mirrors the battler work rows
 * and effect vectors, and resets the effect slots. */
#ifdef NON_MATCHING
NON_MATCHING void func_8009A744(void) {
    u8* slots[6];
    /* FAKE: the base record pointer and the slot counter take retail's s0 and s1 homes (pure-C best 46.40%). */
    FAKE_REG(u8*, base, "s0");
    u8* row;
    u8* cell;
    u8  value;
    /* FAKE: the slot counter takes retail's s1 home (pure-C best 46.40%). */
    FAKE_REG(u8, i, "s1");
    u8 j;

    base     = &g_Characters[MEM_PTR(u8, g_CharSlot)[g_PartyBattleOrder[D_801485C4]]];
    slots[0] = base + 0xE;
    slots[1] = base + 0xF;
    slots[2] = base + 0x10;
    slots[3] = base + 0x11;
    slots[4] = base + 0x12;
    slots[5] = base + 0x13;
    for (i = 0; i < 6; i++) {
        value = s_BattleEquipment[i];
        if (value != 0) {
            if (value != *slots[i]) {
                Item_Remove(D_800B44B0[i], value, 1, 0);
                Item_Add(D_800B44B0[i], *slots[i], 1, 0);
                *slots[i] = s_BattleEquipment[i];
            }
        }
    }
    Char_RebuildStats(base);
    if (g_Battle.party_count != 0) {
        i = 0;
        do {
            cell      = &g_Characters[g_Game.members[i].character_index];
            row       = D_80145F04 + i * BATTLE_PARTY_STRIDE;
            row[0x0E] = cell[0x0E];
            row[0x0F] = cell[0x0F];
            row[0x10] = cell[0x10];
            row[0x11] = cell[0x11];
            row[0x12] = cell[0x12];
            row[0x13] = cell[0x13];
            memcpy(&row[0x3C], &cell[0x1C], 0x10);
            memcpy(&row[0x4C], &cell[0x2C], 0x10);
            i++;
        } while ((u8)i < g_Battle.party_count);
    }
    Battle_ApplyFormationStats();
    j = 0;
    do {
        row = D_80145F20 + j * BATTLE_PARTY_STRIDE;
        if (ACTOR_IN_USE(g_Game.members[j])) {
            memcpy(&row[0x00], &row[0x20], 0x20);
        }
        j++;
    } while (j < 3);
    func_800A4458();
    if (g_Battle.party_count != 0) {
        i = 0;
        do {
            Battle_RescaleStats(i);
            i++;
        } while ((u8)i < g_Battle.party_count);
    }
}
#else
INCLUDE_ASM(func_8009A744);
#endif

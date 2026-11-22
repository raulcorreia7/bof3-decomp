#include "battle_15.h"

/* Applies the equipment chosen in the item list: moves the six slots through Item_Remove and Item_Add and rebuilds the stats. */
/* func_8009A744 */
#ifdef NON_MATCHING
NON_MATCHING void Battle_ApplyEquipment(void) {
    u8* slots[6];
    /* FAKE: the base record pointer and the slot counter take retail's s0 and s1 homes (pure-C best 46.40%). */
    FAKE_REG(Character*, base, "s0");
    Character* member_chr;
    Character* character;
    u8*        stats;
    u8         value;
    u8         party_position;
    u8         character_index;
    /* FAKE: the slot counter takes retail's s1 home (pure-C best 46.40%). */
    FAKE_REG(u8, i, "s1");
    u8 j;

    party_position  = g_PartyBattleOrder[g_UiPanelTasks[18].unk_0C];
    character_index = g_CharSlot[party_position];
    base            = &g_Characters[character_index];
    slots[0]        = &base->equip.weapon;
    slots[1]        = &base->equip.shield;
    slots[2]        = &base->equip.helmet;
    slots[3]        = &base->equip.armor;
    slots[4]        = &base->equip.accessories[0];
    slots[5]        = &base->equip.accessories[1];
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
            character                        = &g_Characters[g_Game.members[i].character_index];
            member_chr                       = &g_Game.members[i].chr;
            member_chr->equip.weapon         = character->equip.weapon;
            member_chr->equip.shield         = character->equip.shield;
            member_chr->equip.helmet         = character->equip.helmet;
            member_chr->equip.armor          = character->equip.armor;
            member_chr->equip.accessories[0] = character->equip.accessories[0];
            member_chr->equip.accessories[1] = character->equip.accessories[1];
            memcpy((u8*)&member_chr->base, (u8*)&character->stats, 0x10);
            memcpy((u8*)&member_chr->base + 0x10, (u8*)&character->stats + 0x10, 0x10);
            i++;
        } while ((u8)i < g_Battle.party_count);
    }
    Battle_ApplyFormationStats();
    j = 0;
    do {
        stats = (u8*)&g_Game.members[j].chr.stats;
        if (ACTOR_IN_USE(g_Game.members[j])) {
            memcpy(stats, stats + 0x20, 0x20);
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
INCLUDE_ASM(Battle_ApplyEquipment);
#endif

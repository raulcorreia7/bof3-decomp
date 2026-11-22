#include "battle_15.h"

/* Rebuilds the target's stats, then refreshes every party member's equipment, stats and battle scaling. */
MATCH void func_8009FB38(void) {
    Character* chr;
    u8*        dst;
    u8*        count;
    u8         battler;
    u8         index;

    Battle_MarkDamageApplied();
    battler = g_Battle.target;
    if (battler < 3) {
        dst = (u8*)&g_Characters[g_Game.members[battler].character_index];
        Char_RebuildStats((Character*)dst);
        index = 0;
        if (g_Battle.party_count != 0) {
            u8* rows;

            rows = D_80145F04;
            do {
                s32 offset;

                offset    = index * BATTLE_PARTY_STRIDE;
                chr       = &g_Characters[g_Game.members[index].character_index];
                dst       = (u8*)(offset + (u32)rows);
                dst[0x0E] = chr->equip.weapon;
                dst[0x0F] = chr->equip.shield;
                dst[0x10] = chr->equip.helmet;
                dst[0x11] = chr->equip.armor;
                dst[0x12] = chr->equip.accessories[0];
                dst[0x13] = chr->equip.accessories[1];
                memcpy(dst + 0x3C, &chr->stats, sizeof(Stats));
                index++;
            } while (index < g_Battle.party_count);
        }
        Battle_ApplyFormationStats();
        count = &g_Battle.party_count;
        index = 0;
        if (*count != 0) {
            do {
                memcpy(&D_80145F20[index * BATTLE_PARTY_STRIDE], &D_80145F20[index * BATTLE_PARTY_STRIDE + 0x20], sizeof(Stats));
                index++;
            } while (index < *count);
        }
        func_800A4458();
        index = 0;
        if (g_Battle.party_count != 0) {
            do {
                Battle_RescaleStats(index);
                index++;
            } while (index < g_Battle.party_count);
        }
    }
}

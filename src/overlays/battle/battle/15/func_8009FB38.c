#include "battle_15.h"

#ifdef NON_MATCHING
NON_MATCHING void func_8009FB38(void) {
    Character* chr;
    u8*        dst;
    u8*        src;
    u8*        count;
    u8         character_index;
    u8         battler;
    u8         index;

    Battle_MarkDamageApplied();
    battler = g_Battle.target;
    if (battler < 3) {
        Char_RebuildStats(&g_Characters[g_Game.members[battler].character_index]);
        index = 0;
        if (g_Battle.party_count != 0) {
            u8* dst_base;

            dst_base = g_Game.members[0].chr.name;
            do {
                s32 offset;

                offset          = index * BATTLE_PARTY_STRIDE;
                character_index = g_Game.members[index].character_index;
                chr             = &g_Characters[character_index];
                dst             = (u8*)(offset + (u32)dst_base);
                dst[0x0E]       = chr->equip.weapon;
                dst[0x0F]       = chr->equip.shield;
                dst[0x10]       = chr->equip.helmet;
                dst[0x11]       = chr->equip.armor;
                dst[0x12]       = chr->equip.accessories[0];
                dst[0x13]       = chr->equip.accessories[1];
                memcpy(dst + 0x3C, &chr->stats, sizeof(Stats));
                index++;
            } while (index < g_Battle.party_count);
        }
        Battle_ApplyFormationStats();
        count = &g_Battle.party_count;
        index = 0;
        if (*count != 0) {
            do {
                s32 offset;

                offset = index * BATTLE_PARTY_STRIDE;
                dst    = D_80145F20 + offset;
                src    = D_80145F20 + offset + 0x20;
                memcpy(dst, src, 0x20);
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
#else
INCLUDE_ASM(func_8009FB38);
#endif

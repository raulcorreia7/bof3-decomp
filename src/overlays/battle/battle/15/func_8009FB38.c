#include "battle_15.h"

#ifdef NON_MATCHING
NON_MATCHING void func_8009FB38(void) {
    Character* stat_base;
    Character* src_base;
    Character* src;
    u8*        dst_base;
    /* FAKE: retail keeps the row destination in a3 across the copy loop; pinned 86.89%. */
    FAKE_REG(u8*, dst_row, "a3");
    volatile u8* active_count;
    u8*          selected_battler_address;
    s32          row_index;
    s32          row_offset;
    u8           battler;
    u8           template_index;
    Battle_MarkDamageApplied();
    selected_battler_address = (u8*)(&g_Battle.target);
    battler                  = *selected_battler_address;
    if (battler < 3U) {
        template_index = g_Game.members[battler].character_index;
        stat_base      = g_Characters;
        Char_RebuildStats((u8*)(&stat_base[template_index]));
        row_index = 0;
        if (g_Battle.party_count != 0) {
            dst_base     = D_80145F04;
            src_base     = stat_base;
            active_count = (volatile u8*)(selected_battler_address - 0xA4);
            do {
                row_offset    = (row_index & BYTE_MASK) * BATTLE_PARTY_STRIDE;
                src           = (Character*)(((&g_Game.members[0].character_index)[row_offset] * PARTY_RECORD_STRIDE) + ((u8*)src_base));
                dst_row       = dst_base + row_offset;
                dst_row[0x0E] = src->equip.weapon;
                dst_row[0x0F] = src->equip.shield;
                dst_row[0x10] = src->equip.helmet;
                dst_row[0x11] = src->equip.armor;
                dst_row[0x12] = src->equip.accessories[0];
                dst_row[0x13] = src->equip.accessories[1];
                memcpy(dst_row + 0x3C, &src->stats.max_hp, 0x20);
                row_index++;
            } while (((u32)(row_index & BYTE_MASK)) < (*active_count));
        }
        Battle_ApplyFormationStats();
        active_count = &g_Battle.party_count;
        FAKE_ORDER_LOCK_BEGIN
            for (row_index = 0; ((u32)(row_index & BYTE_MASK)) < (*active_count); row_index++) {
                row_offset = (row_index & BYTE_MASK) * BATTLE_PARTY_STRIDE;
                memcpy(&D_80145F04[row_offset + 0x1C], &D_80145F04[row_offset + 0x3C], 0x20);
            }
            row_index = 0;
        FAKE_ORDER_LOCK_END;
        func_800A4458();
        if (g_Battle.party_count != 0) {
            do {
                Battle_RescaleStats(row_index);
                row_index++;
            } while (((u32)(row_index & BYTE_MASK)) < g_Battle.party_count);
        }
    }
}
#else
INCLUDE_ASM(func_8009FB38);
#endif

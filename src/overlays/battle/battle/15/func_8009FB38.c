#include "battle_15.h"

/* nonmatching 86.89%: branch@+0x0000; the second refresh loop still schedules differently. */
#ifdef NON_MATCHING
NON_MATCHING void func_8009FB38(void) {
    Character* stat_base;
    Character* src_base;
    Character* src;
    u8*        dst_base;
    /* FAKE: retail keeps the row destination in a3 across the copy loop; pinned 86.89%. */
    MATCH_REG(u8*, dst_row, "a3");
    volatile u8* active_count;
    u8*          selected_battler_address;
    s32          row_index;
    s32          row_offset;
    u8           battler;
    u8           template_index;
    func_800A3F28();
    selected_battler_address = (u8*)(&g_BattleTarget);
    battler                  = *selected_battler_address;
    if (battler < 3U) {
        template_index = D_80145FCC[battler * BATTLE_PARTY_STRIDE];
        stat_base      = g_Characters;
        Char_RebuildStats((u8*)(&stat_base[template_index]));
        row_index = 0;
        if (g_BattlePartyCount != 0) {
            dst_base     = D_80145F04;
            src_base     = stat_base;
            active_count = (volatile u8*)(selected_battler_address - 0xA4);
            do {
                row_offset    = (row_index & BYTE_MASK) * BATTLE_PARTY_STRIDE;
                src           = (Character*)((D_80145FCC[row_offset] * PARTY_RECORD_STRIDE) + ((u8*)src_base));
                dst_row       = dst_base + row_offset;
                dst_row[0x0E] = src->equipment.weapon;
                dst_row[0x0F] = src->equipment.shield;
                dst_row[0x10] = src->equipment.helmet;
                dst_row[0x11] = src->equipment.armor;
                dst_row[0x12] = src->equipment.accessories[0];
                dst_row[0x13] = src->equipment.accessories[1];
                memcpy(dst_row + 0x3C, &src->stats.max_hp, 0x20);
                row_index++;
            } while (((u32)(row_index & BYTE_MASK)) < (*active_count));
        }
        func_800AAA74();
        active_count = &g_BattlePartyCount;
        ORDER_LOCK_BEGIN
            for (row_index = 0; ((u32)(row_index & BYTE_MASK)) < (*active_count); row_index++) {
                row_offset = (row_index & BYTE_MASK) * BATTLE_PARTY_STRIDE;
                memcpy(&D_80145F04[row_offset + 0x1C], &D_80145F04[row_offset + 0x3C], 0x20);
            }
            row_index = 0;
        ORDER_LOCK_END;
        func_800A4458();
        if (g_BattlePartyCount != 0) {
            do {
                func_800A9BD8(row_index);
                row_index++;
            } while (((u32)(row_index & BYTE_MASK)) < g_BattlePartyCount);
        }
    }
}
#else
INCLUDE_ASM(func_8009FB38);
#endif

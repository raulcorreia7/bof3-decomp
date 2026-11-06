#include "battle_15.h"

/* Rescales one battler's panel: player slots defer to the player
 * panel routine; enemy slots scale their quotes and element gauges into the
 * enemy panel, mirror the panel bytes and apply the row's doubling and zeroing
 * flags.
 */
MATCH void func_800A9BD8(u8 slot) {
    if (slot < BATTLE_PARTY_SLOT_COUNT) {
        func_800A9FC4((BattlePanelRecord*)&D_80145F04[slot * BATTLE_PARTY_STRIDE], slot);
    } else {
        s32 row_offset;

        slot -= BATTLE_PARTY_SLOT_COUNT;
        row_offset = slot * BATTLE_ENEMY_STRIDE;

        /* Retail addresses every panel field from its own symbol plus the row
         * offset; a typed row pointer moves the base into a register and does
         * not reproduce the code. */
        FIELD(u16, D_801EB6D4, row_offset + 0x00) = func_801DE0AC(
            FIELD(u16, D_801EB6D4, row_offset + 0x20), (FIELD(s8, D_801EB6D4, row_offset + 0x64) * 2) + 0x64);
        FIELD(u16, D_801EB6D4, row_offset + 0x02) = func_801DE0AC(
            FIELD(u16, D_801EB6D4, row_offset + 0x22), (FIELD(s8, D_801EB6D4, row_offset + 0x65) * 2) + 0x64);
        FIELD(u16, D_801EB6D4, row_offset + 0x04) = func_801DE0AC(
            FIELD(u16, D_801EB6D4, row_offset + 0x24), (FIELD(s8, D_801EB6D4, row_offset + 0x66) * 2) + 0x64);
        FIELD(u16, D_801EB6D4, row_offset + 0x06) = func_801DE0AC(
            FIELD(u16, D_801EB6D4, row_offset + 0x26), (FIELD(s8, D_801EB6D4, row_offset + 0x67) * 2) + 0x64);
        FIELD(u8, D_801EB6D4, row_offset + 0x15) = func_801DE144(FIELD(u8, D_801EB6D4, row_offset + 0x35),
                                                                 (FIELD(s8, D_801EB6D4, row_offset + 0x68) * 2) + 0x64);
        FIELD(u8, D_801EB6D4, row_offset + 0x16) = func_801DE144(FIELD(u8, D_801EB6D4, row_offset + 0x36),
                                                                 (FIELD(s8, D_801EB6D4, row_offset + 0x69) * 2) + 0x64);
        FIELD(u8, D_801EB6D4, row_offset + 0x17) = func_801DE144(FIELD(u8, D_801EB6D4, row_offset + 0x37),
                                                                 (FIELD(s8, D_801EB6D4, row_offset + 0x6A) * 2) + 0x64);
        FIELD(u8, D_801EB6D4, row_offset + 0x18) = func_801DE144(FIELD(u8, D_801EB6D4, row_offset + 0x38),
                                                                 (FIELD(s8, D_801EB6D4, row_offset + 0x6B) * 2) + 0x64);

        FIELD(u8, D_801EB6D4, row_offset + 0x0B) = FIELD(u8, D_801EB6D4, row_offset + 0x2B);
        FIELD(u8, D_801EB6D4, row_offset + 0x0C) = FIELD(u8, D_801EB6D4, row_offset + 0x2C);
        FIELD(u8, D_801EB6D4, row_offset + 0x0D) = FIELD(u8, D_801EB6D4, row_offset + 0x2D);
        FIELD(u8, D_801EB6D4, row_offset + 0x0E) = FIELD(u8, D_801EB6D4, row_offset + 0x2E);
        FIELD(u8, D_801EB6D4, row_offset + 0x0F) = FIELD(u8, D_801EB6D4, row_offset + 0x2F);
        FIELD(u8, D_801EB6D4, row_offset + 0x10) = FIELD(u8, D_801EB6D4, row_offset + 0x30);
        FIELD(u8, D_801EB6D4, row_offset + 0x11) = FIELD(u8, D_801EB6D4, row_offset + 0x31);
        FIELD(u8, D_801EB6D4, row_offset + 0x13) = FIELD(u8, D_801EB6D4, row_offset + 0x33);

        if (FIELD(u32, D_801EB6D4, row_offset + 0x60) & 0x4000) {
            FIELD(u16, D_801EB6D4, row_offset + 0x00) = FIELD(u16, D_801EB6D4, row_offset + 0x00) * 3;
        }
        if (FIELD(u32, D_801EB6D4, row_offset + 0x60) & COMBATANT_FLAG_SELECTION_BONUS) {
            u16 total;
            u16 bonus;

            total                                     = FIELD(u16, D_801EB6D4, row_offset + 0x00);
            bonus                                     = FIELD(u16, D_801EB6D4, row_offset + 0x02);
            FIELD(u16, D_801EB6D4, row_offset + 0x02) = 0;
            FIELD(u16, D_801EB6D4, row_offset + 0x00) = total + bonus;
        }
        FIELD(u16, D_801EB6D4, row_offset + 0x00) = func_801DE0AC(FIELD(u16, D_801EB6D4, row_offset + 0x00), 0x64);
        FIELD(u16, D_801EB6D4, row_offset + 0x02) = func_801DE0AC(FIELD(u16, D_801EB6D4, row_offset + 0x02), 0x64);
    }

    if (g_BattleEnemyBattlers[slot].action_flags & COMBATANT_FLAG_HOLY_RESIST_ZERO) {
        g_BattleEnemyBattlers[slot].stats.resistances[RES_INDEX_HOLY] = 0;
    }
    if (g_BattleEnemyBattlers[slot].action_flags & COMBATANT_FLAG_FIRE_RESIST_ZERO) {
        FIELD(u8, D_801EB6D4, slot * BATTLE_ENEMY_STRIDE + 0x0B) = 0;
    }
}

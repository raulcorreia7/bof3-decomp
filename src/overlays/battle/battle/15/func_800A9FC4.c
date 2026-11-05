#include "battle_15.h"

extern u16 D_80145F26[][160];

/* Rescales the active battler's panel values: blends the four stat
 * quotes and the four element gauges toward their row tables, mirrors the
 * panel bytes and applies the element and status modifiers.
 */
MATCH void func_800A9FC4(BattlePanelRecord* rec, s32 slot) {
    s32 slot_index;
    s32 row_offset;
    s32 table_row;

    slot_index = slot & BYTE_MASK;
    row_offset = slot_index * BATTLE_PARTY_STRIDE;

    rec->unk_20 = func_801DE0AC(rec->unk_40, (FIELD(s8, &D_80145FBC, row_offset) * 2) + 0x64);
    rec->unk_22 = func_801DE0AC(rec->unk_42, (FIELD(s8, &D_80145FBD, row_offset) * 2) + 0x64);
    rec->unk_24 = func_801DE0AC(rec->unk_44, (FIELD(s8, &D_80145FBE, row_offset) * 2) + 0x64);
    rec->unk_26 = func_801DE0AC(rec->unk_46, (FIELD(s8, &D_80145FBF, row_offset) * 2) + 0x64);
    rec->unk_35 = func_801DE144(rec->unk_55, (FIELD(s8, &D_80145FC0, row_offset) * 2) + 0x64);
    rec->unk_36 = func_801DE144(rec->unk_56, (FIELD(s8, &D_80145FC1, row_offset) * 2) + 0x64);
    rec->unk_37 = func_801DE144(rec->unk_57, (FIELD(s8, &D_80145FC2, row_offset) * 2) + 0x64);
    rec->unk_38 = func_801DE144(rec->unk_58, (FIELD(s8, &D_80145FC3, row_offset) * 2) + 0x64);

    rec->unk_2B = rec->unk_4B;
    rec->unk_2C = rec->unk_4C;
    rec->unk_2D = rec->unk_4D;
    rec->unk_2E = rec->unk_4E;
    rec->unk_2F = rec->unk_4F;
    rec->unk_30 = rec->unk_50;
    rec->unk_31 = rec->unk_51;
    rec->unk_33 = rec->unk_53;

    if (g_BattlePartyBattlers[slot_index].action_flags.volatile_value & 1) {
        D_80145F24[slot_index][0] = D_80145F24[slot_index][0] * 3;
    }
    if (g_BattlePartyBattlers[slot_index].action_flags.volatile_value & COMBATANT_FLAG_CHARGING) {
        D_80145F24[slot_index][0] = D_80145F24[slot_index][0] * 3;
    }
    if (g_BattlePartyBattlers[slot_index].action_flags.volatile_value & 0x1000) {
        u16 total;
        u16 bonus;

        total                     = D_80145F24[slot_index][0];
        bonus                     = D_80145F26[slot_index][0];
        D_80145F26[slot_index][0] = 0;
        D_80145F24[slot_index][0] = total + bonus;
    }
    if (g_BattlePartyBattlers[slot_index].action_flags.volatile_value & 2) {
        if (g_DragonForm == 0x16) {
            FIELD(u8, &D_80145F3B, row_offset) = FIELD(u8, &D_80145F3B, row_offset) + 0x1E;
            FIELD(u8, &D_80145F3A, row_offset) = FIELD(u8, &D_80145F3A, row_offset) + 0x1E;
            FIELD(u8, &D_80145F3B, row_offset) = func_801DE144(FIELD(u8, &D_80145F3B, row_offset), 0x64);
            FIELD(u8, &D_80145F3A, row_offset) = func_801DE144(FIELD(u8, &D_80145F3A, row_offset), 0x64);
        }
    }

    table_row = slot & BYTE_MASK;

    if (g_BattlePartyBattlers[table_row].action_flags.volatile_value & COMBATANT_FLAG_HOLY_RESIST_ZERO) {
        g_BattlePartyBattlers[table_row].stats.stats.resistances[RES_SLOT_HOLY] = 0;
    }
    if (g_BattlePartyBattlers[table_row].action_flags.volatile_value & COMBATANT_FLAG_FIRE_RESIST_ZERO) {
        FIELD(u8, &D_80145F2F, table_row * BATTLE_PARTY_STRIDE) = 0;
    }
    D_80145F24[table_row][0] = func_801DE0AC(D_80145F24[table_row][0], 0x64);
    D_80145F26[table_row][0] = func_801DE0AC(D_80145F26[table_row][0], 0x64);
}

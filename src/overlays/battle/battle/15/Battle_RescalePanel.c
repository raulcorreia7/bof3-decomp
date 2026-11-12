#include "battle_15.h"

/* Rescales the active battler's panel values: blends the four stat
 * quotes and the four element gauges toward their row tables, mirrors the
 * panel bytes and applies the element and status modifiers.
 */
/* func_800A9FC4 */
MATCH void Battle_RescalePanel(BattlePanelRecord* rec, s32 slot) {
    s32 party_slot;
    s32 row_offset;
    s32 table_row;

    party_slot = slot & BYTE_MASK;
    row_offset = party_slot * BATTLE_PARTY_STRIDE;

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

    if (g_Game.members[party_slot].u.turn.action_flags.volatile_value & COMBATANT_FLAG_DRAGON_FORM_QUEUED) {
        g_Game.members[party_slot].chr.stats.power = g_Game.members[party_slot].chr.stats.power * 3;
    }
    if (g_Game.members[party_slot].u.turn.action_flags.volatile_value & COMBATANT_FLAG_CHARGING) {
        g_Game.members[party_slot].chr.stats.power = g_Game.members[party_slot].chr.stats.power * 3;
    }
    if (g_Game.members[party_slot].u.turn.action_flags.volatile_value & COMBATANT_FLAG_SELECTION_BONUS) {
        u16 total;
        u16 bonus;

        total                                        = g_Game.members[party_slot].chr.stats.power;
        bonus                                        = g_Game.members[party_slot].chr.stats.defense;
        g_Game.members[party_slot].chr.stats.defense = 0;
        g_Game.members[party_slot].chr.stats.power   = total + bonus;
    }
    if (g_Game.members[party_slot].u.turn.action_flags.volatile_value & COMBATANT_FLAG_DRAGON_FORM) {
        if (g_Battle.dragon_form == 0x16) {
            g_Game.members[party_slot].chr.stats.evasion         = g_Game.members[party_slot].chr.stats.evasion + 0x1E;
            g_Game.members[party_slot].chr.stats.critical_chance = g_Game.members[party_slot].chr.stats.critical_chance + 0x1E;
            g_Game.members[party_slot].chr.stats.evasion         = func_801DE144(g_Game.members[party_slot].chr.stats.evasion, 100);
            g_Game.members[party_slot].chr.stats.critical_chance = func_801DE144(g_Game.members[party_slot].chr.stats.critical_chance, 100);
        }
    }

    table_row = slot & BYTE_MASK;

    if (g_Game.members[table_row].u.turn.action_flags.volatile_value & COMBATANT_FLAG_HOLY_RESIST_ZERO) {
        g_Game.members[table_row].chr.stats.resistances[RES_INDEX_HOLY] = 0;
    }
    if (g_Game.members[table_row].u.turn.action_flags.volatile_value & COMBATANT_FLAG_FIRE_RESIST_ZERO) {
        g_Game.members[table_row].chr.stats.resistances[RES_INDEX_FIRE] = 0;
    }
    g_Game.members[table_row].chr.stats.power   = func_801DE0AC(g_Game.members[table_row].chr.stats.power, 0x64);
    g_Game.members[table_row].chr.stats.defense = func_801DE0AC(g_Game.members[table_row].chr.stats.defense, 0x64);
}

#include "battle_15.h"

/* Rescales the active battler's panel values: blends the four stat
 * quotes and the four element gauges toward their row tables, mirrors the
 * panel bytes and applies the element and status modifiers.
 */
/* func_800A9FC4 */
MATCH void Battle_RescalePanel(Character* rec, s32 slot) {
    s32 party_slot;
    s32 row_offset;
    s32 table_row;

    party_slot = slot & BYTE_MASK;
    row_offset = party_slot * BATTLE_PARTY_STRIDE;

    rec->stats.power           = func_801DE0AC(rec->base.power, (FIELD(s8, &D_80145FBC, row_offset) * 2) + 0x64);
    rec->stats.defense         = func_801DE0AC(rec->base.defense, (FIELD(s8, &D_80145FBD, row_offset) * 2) + 0x64);
    rec->stats.agility         = func_801DE0AC(rec->base.agility, (FIELD(s8, &D_80145FBE, row_offset) * 2) + 0x64);
    rec->stats.intelligence    = func_801DE0AC(rec->base.intelligence, (FIELD(s8, &D_80145FBF, row_offset) * 2) + 0x64);
    rec->stats.reprisal_chance = func_801DE144(rec->base.reprisal_chance, (FIELD(s8, &D_80145FC0, row_offset) * 2) + 0x64);
    rec->stats.critical_chance = func_801DE144(rec->base.critical_chance, (FIELD(s8, &D_80145FC1, row_offset) * 2) + 0x64);
    rec->stats.evasion         = func_801DE144(rec->base.evasion, (FIELD(s8, &D_80145FC2, row_offset) * 2) + 0x64);
    rec->stats.accuracy        = func_801DE144(rec->base.accuracy, (FIELD(s8, &D_80145FC3, row_offset) * 2) + 0x64);

    rec->stats.resistances[0] = rec->base.resistances[0];
    rec->stats.resistances[1] = rec->base.resistances[1];
    rec->stats.resistances[2] = rec->base.resistances[2];
    rec->stats.resistances[3] = rec->base.resistances[3];
    rec->stats.resistances[4] = rec->base.resistances[4];
    rec->stats.resistances[5] = rec->base.resistances[5];
    rec->stats.resistances[6] = rec->base.resistances[6];
    rec->stats.resistances[8] = rec->base.resistances[8];

    if (g_Game.members[party_slot].u.turn.action_flags.volatile_value & BATTLER_ACTION_DRAGON_FORM_QUEUED) {
        g_Game.members[party_slot].chr.stats.power = g_Game.members[party_slot].chr.stats.power * 3;
    }
    if (g_Game.members[party_slot].u.turn.action_flags.volatile_value & BATTLER_ACTION_CHARGING) {
        g_Game.members[party_slot].chr.stats.power = g_Game.members[party_slot].chr.stats.power * 3;
    }
    if (g_Game.members[party_slot].u.turn.action_flags.volatile_value & BATTLER_ACTION_SELECTION_BONUS) {
        u16 total;
        u16 bonus;

        total                                        = g_Game.members[party_slot].chr.stats.power;
        bonus                                        = g_Game.members[party_slot].chr.stats.defense;
        g_Game.members[party_slot].chr.stats.defense = 0;
        g_Game.members[party_slot].chr.stats.power   = total + bonus;
    }
    if (g_Game.members[party_slot].u.turn.action_flags.volatile_value & BATTLER_ACTION_DRAGON_FORM) {
        if (g_Battle.dragon_form == 0x16) {
            g_Game.members[party_slot].chr.stats.evasion         = g_Game.members[party_slot].chr.stats.evasion + 0x1E;
            g_Game.members[party_slot].chr.stats.critical_chance = g_Game.members[party_slot].chr.stats.critical_chance + 0x1E;
            g_Game.members[party_slot].chr.stats.evasion         = func_801DE144(g_Game.members[party_slot].chr.stats.evasion, 100);
            g_Game.members[party_slot].chr.stats.critical_chance = func_801DE144(g_Game.members[party_slot].chr.stats.critical_chance, 100);
        }
    }

    table_row = slot & BYTE_MASK;

    if (g_Game.members[table_row].u.turn.action_flags.volatile_value & BATTLER_ACTION_HOLY_RESIST_ZERO) {
        g_Game.members[table_row].chr.stats.resistances[RES_INDEX_HOLY] = 0;
    }
    if (g_Game.members[table_row].u.turn.action_flags.volatile_value & BATTLER_ACTION_FIRE_RESIST_ZERO) {
        g_Game.members[table_row].chr.stats.resistances[RES_INDEX_FIRE] = 0;
    }
    g_Game.members[table_row].chr.stats.power   = func_801DE0AC(g_Game.members[table_row].chr.stats.power, 0x64);
    g_Game.members[table_row].chr.stats.defense = func_801DE0AC(g_Game.members[table_row].chr.stats.defense, 0x64);
}

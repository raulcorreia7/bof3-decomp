#include "battle_15.h"

/* Rescales one battler's stats: player slots defer to the player
 * stat routine; enemy slots scale their power, defense, agility and intelligence and their
 * reprisal, critical, evasion and accuracy from the base stats by the stat modifier bytes,
 * copy the resistances and apply the row's doubling and zeroing flags.
 */
/* func_800A9BD8 */
MATCH void Battle_RescaleStats(u8 slot) {
    if (slot < BATTLE_PARTY_CHARACTERS_COUNT) {
        Battle_RescalePanel(&g_Game.members[slot].chr, slot);
    } else {
        slot -= BATTLE_PARTY_CHARACTERS_COUNT;

        g_BattleEnemyBattlers[slot].stats.power           = func_801DE0AC(g_BattleEnemyBattlers[slot].base.power, (g_BattleEnemyBattlers[slot].stat_multipliers[0] * 2) + 100);
        g_BattleEnemyBattlers[slot].stats.defense         = func_801DE0AC(g_BattleEnemyBattlers[slot].base.defense, (g_BattleEnemyBattlers[slot].stat_multipliers[1] * 2) + 100);
        g_BattleEnemyBattlers[slot].stats.agility         = func_801DE0AC(g_BattleEnemyBattlers[slot].base.agility, (g_BattleEnemyBattlers[slot].stat_multipliers[2] * 2) + 100);
        g_BattleEnemyBattlers[slot].stats.intelligence    = func_801DE0AC(g_BattleEnemyBattlers[slot].base.intelligence, (g_BattleEnemyBattlers[slot].stat_multipliers[3] * 2) + 100);
        g_BattleEnemyBattlers[slot].stats.reprisal_chance = func_801DE144(g_BattleEnemyBattlers[slot].base.reprisal_chance, (g_BattleEnemyBattlers[slot].stat_multipliers[4] * 2) + 100);
        g_BattleEnemyBattlers[slot].stats.critical_chance = func_801DE144(g_BattleEnemyBattlers[slot].base.critical_chance, (g_BattleEnemyBattlers[slot].stat_multipliers[5] * 2) + 100);
        g_BattleEnemyBattlers[slot].stats.evasion         = func_801DE144(g_BattleEnemyBattlers[slot].base.evasion, (g_BattleEnemyBattlers[slot].stat_multipliers[6] * 2) + 100);
        g_BattleEnemyBattlers[slot].stats.accuracy        = func_801DE144(g_BattleEnemyBattlers[slot].base.accuracy, (g_BattleEnemyBattlers[slot].stat_multipliers[7] * 2) + 100);

        g_BattleEnemyBattlers[slot].stats.resistances[RES_INDEX_FIRE]     = g_BattleEnemyBattlers[slot].base.resistances[RES_INDEX_FIRE];
        g_BattleEnemyBattlers[slot].stats.resistances[RES_INDEX_FROST]    = g_BattleEnemyBattlers[slot].base.resistances[RES_INDEX_FROST];
        g_BattleEnemyBattlers[slot].stats.resistances[RES_INDEX_ELECTRIC] = g_BattleEnemyBattlers[slot].base.resistances[RES_INDEX_ELECTRIC];
        g_BattleEnemyBattlers[slot].stats.resistances[RES_INDEX_EARTH]    = g_BattleEnemyBattlers[slot].base.resistances[RES_INDEX_EARTH];
        g_BattleEnemyBattlers[slot].stats.resistances[RES_INDEX_WIND]     = g_BattleEnemyBattlers[slot].base.resistances[RES_INDEX_WIND];
        g_BattleEnemyBattlers[slot].stats.resistances[RES_INDEX_HOLY]     = g_BattleEnemyBattlers[slot].base.resistances[RES_INDEX_HOLY];
        g_BattleEnemyBattlers[slot].stats.resistances[RES_INDEX_PSIONIC]  = g_BattleEnemyBattlers[slot].base.resistances[RES_INDEX_PSIONIC];
        g_BattleEnemyBattlers[slot].stats.resistances[RES_INDEX_DEATH]    = g_BattleEnemyBattlers[slot].base.resistances[RES_INDEX_DEATH];

        if (g_BattleEnemyBattlers[slot].turn.action_flags.value & 0x4000) {
            g_BattleEnemyBattlers[slot].stats.power = g_BattleEnemyBattlers[slot].stats.power * 3;
        }
        if (g_BattleEnemyBattlers[slot].turn.action_flags.value & BATTLER_ACTION_SELECTION_BONUS) {
            u16 total;
            u16 bonus;

            total                                     = g_BattleEnemyBattlers[slot].stats.power;
            bonus                                     = g_BattleEnemyBattlers[slot].stats.defense;
            g_BattleEnemyBattlers[slot].stats.defense = 0;
            g_BattleEnemyBattlers[slot].stats.power   = total + bonus;
        }
        g_BattleEnemyBattlers[slot].stats.power   = func_801DE0AC(g_BattleEnemyBattlers[slot].stats.power, 100);
        g_BattleEnemyBattlers[slot].stats.defense = func_801DE0AC(g_BattleEnemyBattlers[slot].stats.defense, 100);
    }

    if (g_BattleEnemyBattlers[slot].turn.action_flags.value & BATTLER_ACTION_HOLY_RESIST_ZERO) {
        g_BattleEnemyBattlers[slot].stats.resistances[RES_INDEX_HOLY] = 0;
    }
    if (g_BattleEnemyBattlers[slot].turn.action_flags.value & BATTLER_ACTION_FIRE_RESIST_ZERO) {
        g_BattleEnemyBattlers[slot].stats.resistances[RES_INDEX_FIRE] = 0;
    }
}

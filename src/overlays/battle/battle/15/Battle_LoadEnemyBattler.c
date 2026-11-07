#include "battle_15.h"

/* Copies an area enemy record into an enemy battler and clears its turn state. */
/* func_800AC218 */
MATCH void Battle_LoadEnemyBattler(u8 slot, u8 enemy_index) {
    u8 i;

    for (i = 0; i < ENEMY_NAME_LENGTH; i++) {
        g_BattleEnemyBattlers[slot].name[i] = ENCOUNTER_ENEMIES[enemy_index].name[i];
    }

    g_BattleEnemyBattlers[slot].enemy_id.byte.kind   = ENCOUNTER_ENEMIES[enemy_index].enemy_id.byte.kind;
    g_BattleEnemyBattlers[slot].enemy_id.byte.family = ENCOUNTER_ENEMIES[enemy_index].enemy_id.byte.family;
    g_BattleEnemyBattlers[slot].choice_ai            = ENCOUNTER_ENEMIES[enemy_index].choice_ai;
    g_BattleEnemyBattlers[slot].event_flags          = ENCOUNTER_ENEMIES[enemy_index].event_flags;
    g_BattleEnemyBattlers[slot].zenny                = ENCOUNTER_ENEMIES[enemy_index].zenny;
    g_BattleEnemyBattlers[slot].exp                  = ENCOUNTER_ENEMIES[enemy_index].exp;
    g_BattleEnemyBattlers[slot].level                = ENCOUNTER_ENEMIES[enemy_index].level;

    for (i = 0; i < ENEMY_SKILL_COUNT; i++) {
        g_BattleEnemyBattlers[slot].skills[i] = ENCOUNTER_ENEMIES[enemy_index].initial_skills[i];
    }

    g_BattleEnemyBattlers[slot].status   = ENCOUNTER_ENEMIES[enemy_index].status;
    g_BattleEnemyBattlers[slot].drops[0] = ENCOUNTER_ENEMIES[enemy_index].drops[0];
    g_BattleEnemyBattlers[slot].drops[1] = ENCOUNTER_ENEMIES[enemy_index].drops[1];

    g_BattleEnemyBattlers[slot].hp = g_BattleEnemyBattlers[slot].base.max_hp = ENCOUNTER_ENEMIES[enemy_index].hp;
    g_BattleEnemyBattlers[slot].ap = g_BattleEnemyBattlers[slot].base.max_ap = ENCOUNTER_ENEMIES[enemy_index].ap;
    g_BattleEnemyBattlers[slot].base.power                                   = ENCOUNTER_ENEMIES[enemy_index].power;
    g_BattleEnemyBattlers[slot].base.defense                                 = ENCOUNTER_ENEMIES[enemy_index].defense;
    g_BattleEnemyBattlers[slot].base.agility                                 = ENCOUNTER_ENEMIES[enemy_index].agility;
    g_BattleEnemyBattlers[slot].base.intellect                               = ENCOUNTER_ENEMIES[enemy_index].intellect;
    g_BattleEnemyBattlers[slot].base.resistances[RES_INDEX_FIRE] =
        ENCOUNTER_ENEMIES[enemy_index].resistances[RES_INDEX_FIRE];
    g_BattleEnemyBattlers[slot].base.resistances[RES_INDEX_FROST] =
        ENCOUNTER_ENEMIES[enemy_index].resistances[RES_INDEX_FROST];
    g_BattleEnemyBattlers[slot].base.resistances[RES_INDEX_ELECTRIC] =
        ENCOUNTER_ENEMIES[enemy_index].resistances[RES_INDEX_ELECTRIC];
    g_BattleEnemyBattlers[slot].base.resistances[RES_INDEX_EARTH] =
        ENCOUNTER_ENEMIES[enemy_index].resistances[RES_INDEX_EARTH];
    g_BattleEnemyBattlers[slot].base.resistances[RES_INDEX_WIND] =
        ENCOUNTER_ENEMIES[enemy_index].resistances[RES_INDEX_WIND];
    g_BattleEnemyBattlers[slot].base.resistances[RES_INDEX_HOLY] =
        ENCOUNTER_ENEMIES[enemy_index].resistances[RES_INDEX_HOLY];
    g_BattleEnemyBattlers[slot].base.resistances[RES_INDEX_PSIONIC] =
        ENCOUNTER_ENEMIES[enemy_index].resistances[RES_INDEX_PSIONIC];
    g_BattleEnemyBattlers[slot].base.resistances[RES_INDEX_STATUS] =
        ENCOUNTER_ENEMIES[enemy_index].resistances[RES_INDEX_STATUS];
    g_BattleEnemyBattlers[slot].base.resistances[RES_INDEX_DEATH] =
        ENCOUNTER_ENEMIES[enemy_index].resistances[RES_INDEX_DEATH];
    g_BattleEnemyBattlers[slot].stats = g_BattleEnemyBattlers[slot].base;

    g_BattleEnemyBattlers[slot].unk_F0                  = ENCOUNTER_ENEMIES[enemy_index].unk_84[0];
    g_BattleEnemyBattlers[slot].unk_F1                  = ENCOUNTER_ENEMIES[enemy_index].unk_84[1];
    g_BattleEnemyBattlers[slot].kind                    = enemy_index;
    g_BattleEnemyBattlers[slot].turn.counter            = 0;
    g_BattleEnemyBattlers[slot].turn.damage_flags.value = g_BattleEnemyBattlers[slot].turn.action_flags.value = 0;
    g_BattleEnemyBattlers[slot].unk_112                                                                       = 0;
    g_BattleEnemyBattlers[slot].unk_113                                                                       = 0;
    g_BattleEnemyBattlers[slot].unk_114                                                                       = 0;
    g_BattleEnemyBattlers[slot].unk_115                                                                       = 0;
    for (i = 0; i < ENEMY_STAT_MULTIPLIER_COUNT; i++) {
        g_BattleEnemyBattlers[slot].stat_multipliers[i] = 0;
    }
}

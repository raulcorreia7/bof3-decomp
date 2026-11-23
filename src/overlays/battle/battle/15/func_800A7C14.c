#include "battle_15.h"

/* Rebuilds the stat display template from a dragon-form row and applies it to the active member's live record. */
#ifdef NON_MATCHING
NON_MATCHING void func_800A7C14(u8 slot) {
    Character* battler;
    Character* character;
    u8         battler_index;
    u8         ability;
    u8         ability_id;
    u8         index;
    u8         resistance;
    s16        stat;
    s16        max_hp;

    for (battler_index = 0; battler_index < g_Battle.party_count; battler_index++) {
        s_BattleBattlerTemplates[battler_index] = g_Game.members[battler_index];
    }

    battler   = &g_Game.members[g_Battle.active_battler].chr;
    character = &g_Characters[g_Game.members[g_Battle.active_battler].character_index];

    D_801EBEF0.max_hp     = func_801DE0F8(character->base.max_hp, D_800B4EE0[slot][0] * 10);
    max_hp                = D_801EBEF0.max_hp - ((D_801EBEF0.max_hp * character->fatigue + 5) / 10);
    battler->base.max_hp  = max_hp;
    battler->stats.max_hp = max_hp;
    battler->hp           = max_hp;

    D_801EBEF0.power     = battler->base.power;
    stat                 = func_801DE0AC(battler->base.power, D_800B4EE0[slot][1] * 10);
    battler->base.power  = stat;
    battler->stats.power = stat;
    D_801EBEF0.power     = stat - D_801EBEF0.power;

    D_801EBEF0.defense     = battler->base.defense;
    stat                   = func_801DE0AC(battler->base.defense, D_800B4EE0[slot][2] * 10);
    battler->base.defense  = stat;
    battler->stats.defense = stat;
    D_801EBEF0.defense     = stat - D_801EBEF0.defense;

    D_801EBEF0.agility     = battler->base.agility;
    stat                   = func_801DE0AC(battler->base.agility, D_800B4EE0[slot][3] * 10);
    battler->base.agility  = stat;
    battler->stats.agility = stat;
    D_801EBEF0.agility     = stat - D_801EBEF0.agility;

    D_801EBEF0.intelligence     = battler->base.intelligence;
    stat                        = func_801DE0AC(battler->base.intelligence, D_800B4EE0[slot][4] * 10);
    battler->base.intelligence  = stat;
    battler->stats.intelligence = stat;
    D_801EBEF0.intelligence     = stat - D_801EBEF0.intelligence;

    resistance                    = D_800B4EE0[slot][5];
    battler->base.resistances[0]  = resistance;
    battler->stats.resistances[0] = resistance;
    D_801EBEF0.resistances[0]     = resistance;
    resistance                    = D_800B4EE0[slot][6];
    battler->base.resistances[1]  = resistance;
    battler->stats.resistances[1] = resistance;
    D_801EBEF0.resistances[1]     = resistance;
    resistance                    = D_800B4EE0[slot][7];
    battler->base.resistances[2]  = resistance;
    battler->stats.resistances[2] = resistance;
    D_801EBEF0.resistances[2]     = resistance;
    resistance                    = D_800B4EE0[slot][8];
    battler->base.resistances[3]  = resistance;
    battler->stats.resistances[3] = resistance;
    D_801EBEF0.resistances[3]     = resistance;
    resistance                    = D_800B4EE0[slot][9];
    battler->base.resistances[4]  = resistance;
    battler->stats.resistances[4] = resistance;
    D_801EBEF0.resistances[4]     = resistance;
    resistance                    = D_800B4EE0[slot][10];
    battler->base.resistances[5]  = resistance;
    battler->stats.resistances[5] = resistance;
    D_801EBEF0.resistances[5]     = resistance;
    resistance                    = D_800B4EE0[slot][11];
    battler->base.resistances[6]  = resistance;
    battler->stats.resistances[6] = resistance;
    D_801EBEF0.resistances[6]     = resistance;
    resistance                    = D_800B4EE0[slot][12];
    battler->base.resistances[7]  = resistance;
    battler->stats.resistances[7] = resistance;
    D_801EBEF0.resistances[7]     = resistance;
    resistance                    = D_800B4EE0[slot][13];
    battler->base.resistances[8]  = resistance;
    battler->stats.resistances[8] = resistance;
    D_801EBEF0.resistances[8]     = resistance;

    ability = 0;
    for (index = 0; index < 8; index++, ability++) {
        if (ability == CHARACTER_ABILITY_COUNT - 1) {
            break;
        }
        ability_id = D_800B5008[slot][index];
        if (ability_id == 0) {
            break;
        }
        battler->abilities.attack[ability] = ability_id;
    }
    battler->abilities.attack[ability] = 0xD9;
    for (ability++; ability < CHARACTER_ABILITY_COUNT; ability++) {
        battler->abilities.attack[ability] = 0;
    }
}
#else
INCLUDE_ASM(func_800A7C14);
#endif

#include "battle_15.h"

#ifdef NON_MATCHING
NON_MATCHING void func_800A7C14(u8 slot) {
    PartyMember* battler;
    Character*   character;
    u8           battler_index;
    u8           ability;
    u8           byte_value;
    s16          value;
    s16          max_hp;

    for (battler_index = 0; battler_index < g_Battle.party_count; battler_index++) {
        s_BattleBattlerTemplates[battler_index] = g_Game.members[battler_index];
    }

    battler   = &g_Game.members[g_Battle.active_battler];
    character = &g_Characters[battler->character_index];

    D_801EBEF0.max_hp         = func_801DE0F8(character->base.max_hp, D_800B4EE0[slot][0]);
    max_hp                    = D_801EBEF0.max_hp - ((D_801EBEF0.max_hp * battler->chr.fatigue + 5) / 10);
    battler->chr.base.max_hp  = max_hp;
    battler->chr.stats.max_hp = max_hp;
    battler->chr.hp           = max_hp;

    D_801EBEF0.power         = battler->chr.base.power;
    value                    = func_801DE0AC(battler->chr.base.power, D_800B4EE0[slot][1] * 10);
    battler->chr.base.power  = value;
    battler->chr.stats.power = value;
    D_801EBEF0.power         = value - D_801EBEF0.power;

    D_801EBEF0.defense         = battler->chr.base.defense;
    value                      = func_801DE0AC(battler->chr.base.defense, D_800B4EE0[slot][2] * 10);
    battler->chr.base.defense  = value;
    battler->chr.stats.defense = value;
    D_801EBEF0.defense         = value - D_801EBEF0.defense;

    D_801EBEF0.agility         = battler->chr.base.agility;
    value                      = func_801DE0AC(battler->chr.base.agility, D_800B4EE0[slot][3] * 10);
    battler->chr.base.agility  = value;
    battler->chr.stats.agility = value;
    D_801EBEF0.agility         = value - D_801EBEF0.agility;

    D_801EBEF0.intelligence         = battler->chr.base.intelligence;
    value                           = func_801DE0AC(battler->chr.base.intelligence, D_800B4EE0[slot][4] * 10);
    battler->chr.base.intelligence  = value;
    battler->chr.stats.intelligence = value;
    D_801EBEF0.intelligence         = value - D_801EBEF0.intelligence;

    byte_value                        = D_800B4EE0[slot][5];
    battler->chr.base.resistances[0]  = byte_value;
    battler->chr.stats.resistances[0] = byte_value;
    D_801EBEF0.resistances[0]         = byte_value;
    byte_value                        = D_800B4EE0[slot][6];
    battler->chr.base.resistances[1]  = byte_value;
    battler->chr.stats.resistances[1] = byte_value;
    D_801EBEF0.resistances[1]         = byte_value;
    byte_value                        = D_800B4EE0[slot][7];
    battler->chr.base.resistances[2]  = byte_value;
    battler->chr.stats.resistances[2] = byte_value;
    D_801EBEF0.resistances[2]         = byte_value;
    byte_value                        = D_800B4EE0[slot][8];
    battler->chr.base.resistances[3]  = byte_value;
    battler->chr.stats.resistances[3] = byte_value;
    D_801EBEF0.resistances[3]         = byte_value;
    byte_value                        = D_800B4EE0[slot][9];
    battler->chr.base.resistances[4]  = byte_value;
    battler->chr.stats.resistances[4] = byte_value;
    D_801EBEF0.resistances[4]         = byte_value;
    byte_value                        = D_800B4EE0[slot][10];
    battler->chr.base.resistances[5]  = byte_value;
    battler->chr.stats.resistances[5] = byte_value;
    D_801EBEF0.resistances[5]         = byte_value;
    byte_value                        = D_800B4EE0[slot][11];
    battler->chr.base.resistances[6]  = byte_value;
    battler->chr.stats.resistances[6] = byte_value;
    D_801EBEF0.resistances[6]         = byte_value;
    byte_value                        = D_800B4EE0[slot][12];
    battler->chr.base.resistances[7]  = byte_value;
    battler->chr.stats.resistances[7] = byte_value;
    D_801EBEF0.resistances[7]         = byte_value;
    byte_value                        = D_800B4EE0[slot][13];
    battler->chr.base.resistances[8]  = byte_value;
    battler->chr.stats.resistances[8] = byte_value;
    D_801EBEF0.resistances[8]         = byte_value;

    for (ability = 0; ability < 8; ability++) {
        byte_value = D_800B5008[slot][ability];
        if (byte_value == 0) {
            break;
        }
        battler->chr.abilities.attack[ability] = byte_value;
    }
    battler->chr.abilities.attack[ability] = 0xD9;
    for (ability++; ability < CHARACTER_ABILITY_COUNT; ability++) {
        battler->chr.abilities.attack[ability] = 0;
    }
}
#else
INCLUDE_ASM(func_800A7C14);
#endif

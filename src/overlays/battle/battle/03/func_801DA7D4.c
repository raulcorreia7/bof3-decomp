#include "battle_03.h"

/* Orders the live party members by agility and rebuilds the command row list
 * from the surviving ones, after sizing the enemy side. */
MATCH void func_801DA7D4(void) {
    BattleRank entries[BATTLE_PARTY_CHARACTERS_COUNT];
    BattleRank temp;
    u8         n;
    u16        total;
    u8         i;
    u8         count;
    u16        agility;
    u16        maximum;

    total   = 0;
    maximum = 0;
    for (i = BATTLE_PARTY_CHARACTERS_COUNT; i < COMBATANT_COUNT; i++) {
        if (D_801463BA == 0 || (ENEMY_COMBATANT(i).turn.action_flags.value & BATTLER_ACTION_PREEMPTIVE_TURN)) {
            if (func_801DB9E4(i)) {
                agility = ENEMY_COMBATANT(i).stats.agility;
                total += agility;
                if (maximum < agility) {
                    maximum = agility;
                }
            }
        }
    }
    for (n = (u8)total >> 8, i = 0; i < BATTLE_PARTY_CHARACTERS_COUNT; i++) {
        if (D_801463BA == 0 || (g_Game.members[i].u.turn.action_flags.value & BATTLER_ACTION_PREEMPTIVE_TURN)) {
            if (func_801DB844(i)) {
                entries[n].value = g_Game.members[i].chr.stats.agility;
                entries[n].index = i;
                n++;
            }
        }
    }
    count = n;
    if (count >= 2) {
        for (n = 0; n < count - 1; n++) {
            for (i = n + 1; i < count; i++) {
                if (entries[n].value < entries[i].value) {
                    temp       = entries[n];
                    entries[n] = entries[i];
                    entries[i] = temp;
                }
            }
        }
    }
    for (i = 0; i < BATTLE_PARTY_CHARACTERS_COUNT; i++) {
        D_801462F6[i] = 0xFF;
    }
    g_Battle.command_count = 0;
    for (i = 0; i < count; i++) {
        if (func_801DB844((u8)entries[i].index)) {
            D_801462F6[(s8)g_Battle.command_count] = entries[i].index;
            g_Battle.command_count++;
        }
    }
}

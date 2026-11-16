#include "battle_03.h"

/* The number of party rows the command list holds. */
#define BATTLE_COMMAND_MAX 3

#ifdef NON_MATCHING
NON_MATCHING void func_801DA7D4(void) {
    BattleRank entries[BATTLE_COMMAND_MAX];
    BattleRank temp;
    u8         total;
    u8         maximum;
    u16        agility;
    u8         index;
    u8         left;
    u8         right;

    total   = 0;
    maximum = 0;
    for (index = 3; index < 11; index++) {
        if (D_801463BA == 0 || (g_BattleEnemyBattlers[index - 3].turn.action_flags.value & BATTLER_ACTION_PREEMPTIVE_TURN)) {
            if (func_801DB9E4(index)) {
                agility = g_BattleEnemyBattlers[index - 3].stats.agility;
                total += agility;
                if (maximum < agility) {
                    maximum = agility;
                }
            }
        }
    }

    total = 0;
    for (index = 0; index < BATTLE_COMMAND_MAX; index++) {
        if (D_801463BA == 0 || (g_Game.members[index].u.turn.action_flags.volatile_value & BATTLER_ACTION_PREEMPTIVE_TURN)) {
            if (func_801DB844(index)) {
                entries[total].index = index;
                entries[total].value = g_Game.members[index].chr.stats.agility;
                total++;
            }
        }
    }

    maximum = total;
    if (maximum >= 2) {
        for (left = 0; left < maximum - 1; left++) {
            for (right = left + 1; right < maximum; right++) {
                if (entries[left].value < entries[right].value) {
                    temp           = entries[left];
                    entries[left]  = entries[right];
                    entries[right] = temp;
                }
            }
        }
    }

    for (index = 0; index < BATTLE_COMMAND_MAX; index++) {
        D_801462F6[index] = 0xFF;
    }
    g_Battle.command_count = 0;
    for (index = 0; index < maximum; index++) {
        if (func_801DB844((u8)entries[index].index)) {
            D_801462F6[g_Battle.command_count] = entries[index].index;
            g_Battle.command_count++;
        }
    }
}
#else
INCLUDE_ASM(func_801DA7D4);
#endif

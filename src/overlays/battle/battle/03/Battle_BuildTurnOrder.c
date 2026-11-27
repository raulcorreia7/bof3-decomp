#include "battle_03.h"

/* func_801DAAE4 */
#ifdef NON_MATCHING
NON_MATCHING void Battle_BuildTurnOrder(void) {
    BattleRank temp;
    u16        total;
    u16        maximum;
    u16        agility;
    u8         index;
    u8         count;
    u8         left;
    u8         right;
    u8         rank;
    s32        mode;
    u8*        ability_mode;

    total   = 0;
    maximum = 0;
    for (index = 0; index < 3; index++) {
        if (D_801463BA == 0 || (g_Game.members[index].u.turn.action_flags.volatile_value & BATTLER_ACTION_PREEMPTIVE_TURN)) {
            if (func_801DB9E4(index)) {
                agility = g_Game.members[index].chr.stats.agility;
                total += agility;
                if (maximum < agility) {
                    maximum = agility;
                }
            }
        }
    }

    count = (u8)total >> 8;
    for (index = 0; index < 3; index++) {
        if (D_801463BA == 0 || (g_Game.members[index].u.turn.action_flags.volatile_value & BATTLER_ACTION_PREEMPTIVE_TURN)) {
            if (func_801DB9E4(index)) {
                D_801EB550[count].index = index;
                D_801EB550[count].value = 0;
                if (g_Game.members[index].u.turn.command.type == BATTLE_COMMAND_ABILITY) {
                    ability_mode = (u8*)&g_Abilities[g_Game.members[index].u.turn.command.id].type;
                    mode         = *ability_mode;
                    switch (mode) {
                        case 0:
                            D_801EB550[count].value = 4;
                            break;
                        case 1:
                        case 3:
                            D_801EB550[count].value = 2;
                            break;
                    }
                }
                if (g_Game.members[index].u.turn.command.type == BATTLE_COMMAND_ITEM) {
                    D_801EB550[count].value = 1;
                }
                rank                    = func_801DB434(g_Game.members[index].chr.level, 1);
                D_801EB550[count].value = (s16)(D_801EB550[count].value * ((u16*)g_BattleTurnPriorityMultipliers)[rank]) / 100;
                D_801EB550[count].value += g_Game.members[index].chr.stats.agility;
                count++;
            }
        }
    }

    for (index = 3; index < 11; index++) {
        if (D_801463BA == 0 || (g_BattleEnemyBattlers[index - 3].turn.action_flags.value & BATTLER_ACTION_PREEMPTIVE_TURN)) {
            if (func_801DB9E4(index)) {
                rank                    = func_801DB434(g_BattleEnemyBattlers[index - 3].level, 0);
                D_801EB550[count].value = g_BattleEnemyBattlers[index - 3].stats.agility + D_801EAF48[rank][rand() & 0xF];
                D_801EB550[count].index = index;
                count++;
            }
        }
    }

    g_Battle.turn_count = count;
    if (count >= 2) {
        for (left = 0; left < g_Battle.turn_count - 1; left++) {
            for (right = left + 1; right < g_Battle.turn_count; right++) {
                if (D_801EB550[left].value < D_801EB550[right].value) {
                    temp              = D_801EB550[left];
                    D_801EB550[left]  = D_801EB550[right];
                    D_801EB550[right] = temp;
                }
            }
        }
    }

    for (index = 0; index < 11; index++) {
        g_Battle.turn_order[index] = 0xFF;
    }
    for (index = 0; index < g_Battle.turn_count; index++) {
        g_Battle.turn_order[index] = D_801EB550[index].index;
    }
    g_Battle.turn_cursor = 0;
}
#else
INCLUDE_ASM(Battle_BuildTurnOrder);
#endif

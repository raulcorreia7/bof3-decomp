#include "battle_03.h"

/* func_801DAAE4 */
#ifdef NON_MATCHING
NON_MATCHING void Battle_BuildTurnOrder(void) {
    u16 total;
    u16 maximum;
    u32 index;
    u32 count;
    u32 left;
    u32 right;

    total   = 0u;
    maximum = 0u;
    index   = 0u;
    while ((u8)index < 3u) {
        if ((D_801463BA == 0u) ||
            ((g_Game.members[(u8)index].turn.action_flags.volatile_value & COMBATANT_FLAG_PREEMPTIVE_TURN) != 0u)) {
            if (func_801DB9E4((u8)index) != 0u) {
                u16 value;

                value = g_Game.members[(u8)index].chr.stats.agility;
                total += value;
                CLAMP_MIN(maximum, value);
            }
        }
        index += 1u;
    }

    count = 0u;
    index = 0u;
    while ((u8)index < 3u) {
        if ((D_801463BA == 0u) ||
            ((g_Game.members[(u8)index].turn.action_flags.volatile_value & COMBATANT_FLAG_PREEMPTIVE_TURN) != 0u)) {
            if (func_801DB9E4((u8)index) != 0u) {
                s16 score;
                s32 mode;

                D_801EB550[(u8)count].index = (u8)index;
                D_801EB550[(u8)count].value = 0;
                if (g_Game.members[(u8)index].turn.command.type == BATTLE_COMMAND_ABILITY) {
                    mode = D_801CA718[g_Game.members[(u8)index].turn.command.id][1];
                    if (mode == 1 || mode == 3) {
                        D_801EB550[(u8)count].value = 2;
                    } else if (mode == 0) {
                        D_801EB550[(u8)count].value = 4;
                    }
                }
                if (g_Game.members[(u8)index].turn.command.type == BATTLE_COMMAND_ITEM) {
                    D_801EB550[(u8)count].value = 1;
                }
                score = D_801EB550[(u8)count].value;
                score =
                    (s16)(score *
                          g_BattleTurnPriorityMultipliers[(u8)func_801DB434(g_Game.members[(u8)index].chr.level, 1u)]) /
                    100;
                D_801EB550[(u8)count].value = score;
                count += 1u;
                D_801EB550[(u8)count - 1u].value = score + g_Game.members[(u8)index].chr.stats.agility;
            }
        }
        index += 1u;
    }

    index = 3u;
    while ((u8)index < 11u) {
        if ((D_801463BA == 0u) ||
            ((g_BattleEnemyBattlers[(u8)index - 3u].turn.action_flags.value & COMBATANT_FLAG_PREEMPTIVE_TURN) != 0u)) {
            if (func_801DB9E4((u8)index) != 0u) {
                u32 slot;
                u32 rank;

                slot                        = (u8)index - 3u;
                rank                        = func_801DB434(g_BattleEnemyBattlers[slot].level, 0u);
                D_801EB550[(u8)count].index = (u8)index;
                count += 1u;
                D_801EB550[(u8)count - 1u].value =
                    g_BattleEnemyBattlers[slot].stats.agility + D_801EAF48[((u8)rank * 0x10u) + RANDOM_MASK(0xFu)];
            }
        }
        index += 1u;
    }

    g_Battle.turn_count = (u8)count;
    if ((u8)count > 1u) {
        left = 0u;
        while ((u8)left < g_Battle.turn_count - 1) {
            right = left + 1u;
            while ((u8)right < g_Battle.turn_count) {
                if (D_801EB550[(u8)left].value < D_801EB550[(u8)right].value) {
                    BattleRank temp;

                    temp                  = D_801EB550[(u8)left];
                    D_801EB550[(u8)left]  = D_801EB550[(u8)right];
                    D_801EB550[(u8)right] = temp;
                }
                right += 1u;
            }
            left += 1u;
        }
    }

    index = 0u;
    while ((u8)index < 11u) {
        g_Battle.turn_order[index] = 0xFFu;
        index += 1u;
    }

    index = 0u;
    while ((u8)index < g_Battle.turn_count) {
        g_Battle.turn_order[index] = (u8)D_801EB550[(u8)index].index;
        index += 1u;
    }

    g_Battle.turn_cursor = 0u;
}
#else
INCLUDE_ASM(Battle_BuildTurnOrder);
#endif

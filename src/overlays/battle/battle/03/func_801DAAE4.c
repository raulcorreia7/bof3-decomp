#include "battle_03.h"

#ifdef NON_MATCHING
NON_MATCHING void func_801DAAE4(void) {
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
            ((g_BattlePartyBattlers[(u8)index].action_flags.volatile_value & COMBATANT_FLAG_PREEMPTIVE_TURN) != 0u)) {
            if (func_801DB9E4((u8)index) != 0u) {
                u16 value;

                value = g_BattlePartyBattlers[(u8)index].stats.stats.agility;
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
            ((g_BattlePartyBattlers[(u8)index].action_flags.volatile_value & COMBATANT_FLAG_PREEMPTIVE_TURN) != 0u)) {
            if (func_801DB9E4((u8)index) != 0u) {
                s16 score;
                s32 mode;

                D_801EB550[(u8)count].index = (u8)index;
                D_801EB550[(u8)count].value = 0;
                if (g_BattlePartyBattlers[(u8)index].mode_119 == 4u) {
                    mode = D_801CA719[g_BattlePartyBattlers[(u8)index].command].value;
                    if (mode == 1 || mode == 3) {
                        D_801EB550[(u8)count].value = 2;
                    } else if (mode == 0) {
                        D_801EB550[(u8)count].value = 4;
                    }
                }
                if (g_BattlePartyBattlers[(u8)index].mode_119 == 5u) {
                    D_801EB550[(u8)count].value = 1;
                }
                score                       = D_801EB550[(u8)count].value;
                score                       = (s16)(score * g_BattleTurnPriorityMultipliers[(u8)func_801DB434(
                                                                g_BattlePartyBattlers[(u8)index].stats.level, 1u)]) /
                                              100;
                D_801EB550[(u8)count].value = score;
                count += 1u;
                D_801EB550[(u8)count - 1u].value = score + g_BattlePartyBattlers[(u8)index].stats.stats.agility;
            }
        }
        index += 1u;
    }

    index = 3u;
    while ((u8)index < 11u) {
        if ((D_801463BA == 0u) || ((D_801EB630[(u8)index - 3u].action_flags & COMBATANT_FLAG_PREEMPTIVE_TURN) != 0u)) {
            if (func_801DB9E4((u8)index) != 0u) {
                u32 slot;
                u32 rank;

                slot                        = (u8)index - 3u;
                rank                        = func_801DB434(D_801EB630[slot].unk_88, 0u);
                D_801EB550[(u8)count].index = (u8)index;
                count += 1u;
                D_801EB550[(u8)count - 1u].value =
                    D_801EB630[slot].stats.agility + D_801EAF48[((u8)rank * 0x10u) + (RANDOM_MASK(0xFu))];
            }
        }
        index += 1u;
    }

    D_80146323 = (u8)count;
    if ((u8)count > 1u) {
        left = 0u;
        while ((u8)left < D_80146323 - 1) {
            right = left + 1u;
            while ((u8)right < D_80146323) {
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
        BATTLE_GLOBAL_BYTE_630C(index) = 0xFFu;
        index += 1u;
    }

    index = 0u;
    while ((u8)index < D_80146323) {
        BATTLE_GLOBAL_BYTE_630C(index) = (u8)D_801EB550[(u8)index].index;
        index += 1u;
    }

    D_80146322 = 0u;
}
#else
INCLUDE_ASM(func_801DAAE4);
#endif

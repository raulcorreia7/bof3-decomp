#include "battle_03.h"

/* Orders the live party members by agility and rebuilds the command row list
 * from the surviving ones, after sizing the enemy side. */
#ifdef NON_MATCHING
NON_MATCHING void func_801DA7D4(void) {
    BattleRank entries[BATTLE_PARTY_CHARACTERS_COUNT];
    BattleRank temp;
    s32        total;
    u32        maximum;
    u16        agility;
    s32        index;

    total   = 0;
    maximum = 0;
    for (index = BATTLE_PARTY_CHARACTERS_COUNT; (u32)(index & BYTE_MASK) < COMBATANT_COUNT; index++) {
        if (D_801463BA == 0 || (ENEMY_COMBATANT(index & BYTE_MASK).turn.action_flags.value & BATTLER_ACTION_PREEMPTIVE_TURN)) {
            if (func_801DB9E4(index & BYTE_MASK)) {
                agility = ENEMY_COMBATANT(index & BYTE_MASK).stats.agility;
                total += agility;
                if (maximum < agility) {
                    maximum = agility;
                }
            }
        }
    }

    total = 0;
    for (index = 0; (u32)(index & BYTE_MASK) < BATTLE_PARTY_CHARACTERS_COUNT; index++) {
        if (D_801463BA == 0 || (g_Game.members[index & BYTE_MASK].u.turn.action_flags.value & BATTLER_ACTION_PREEMPTIVE_TURN)) {
            if (func_801DB844(index & BYTE_MASK)) {
                entries[total & BYTE_MASK].index = index & BYTE_MASK;
                entries[total & BYTE_MASK].value = g_Game.members[index & BYTE_MASK].chr.stats.agility;
                total += 1;
            }
        }
    }

    maximum = total;
    if ((maximum & BYTE_MASK) >= 2) {
        for (total = 0; (total & BYTE_MASK) < (maximum & BYTE_MASK) - 1; total++) {
            for (index = total + 1; (index & BYTE_MASK) < (maximum & BYTE_MASK); index++) {
                if (entries[total & BYTE_MASK].value < entries[index & BYTE_MASK].value) {
                    temp                       = entries[total & BYTE_MASK];
                    entries[total & BYTE_MASK] = entries[index & BYTE_MASK];
                    entries[index & BYTE_MASK] = temp;
                }
            }
        }
    }

    for (index = 0; (u32)(index & BYTE_MASK) < BATTLE_PARTY_CHARACTERS_COUNT; index++) {
        D_801462F6[index & BYTE_MASK] = 0xFF;
    }
    g_Battle.command_count = 0;
    for (index = 0; (u32)(index & BYTE_MASK) < (maximum & BYTE_MASK); index++) {
        if (func_801DB844(entries[index & BYTE_MASK].index)) {
            D_801462F6[(s8)g_Battle.command_count] = entries[index & BYTE_MASK].index;
            g_Battle.command_count++;
        }
    }
}
#else
INCLUDE_ASM(func_801DA7D4);
#endif

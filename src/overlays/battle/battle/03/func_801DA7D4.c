#include "battle_03.h"

/* One command-list entry: the row's action value and the row index. */
#define BATTLE_COMMAND_ENTRY_SIZE 4

typedef struct BattleCommand {
    s16 value;
    s16 index;
} BattleCommand;

ASSERT_SIZE(BattleCommand, BATTLE_COMMAND_ENTRY_SIZE);

/* The number of command-list rows a battle can hold. */
#define BATTLE_COMMAND_MAX 3

/* nonmatching unmeasured: tried the command-list build with the entry table indexed directly (a `table` alias hoisted
 * the stack array into s4 where retail recomputes sp+0x10 per use), the wide max and the byte accumulator (75.00%).
 * residual: retail seeds the s2 accumulator at entry and saves s2 first; ours saves s3 first and emits the s2 store
 * later, and ten branch hunks follow from that. resume: a source shape whose sum accumulator is live from entry. */
#ifdef NON_MATCHING
NON_MATCHING void func_801DA7D4(void) {
    BattleCommand  entries[BATTLE_COMMAND_MAX];
    BattleCommand* entry;
    BattleCommand* other;
    BattleCommand  temp;
    s32            scan;
    u32            count;
    u8             sum;
    u32            max;
    u16            value;
    u32            scan_index;
    u8             i;
    u8             total;
    s8*            cursor;

    max = 0;
    sum = 0;
    i   = 3;
    do {
        if ((D_801463BA == 0) || (ENEMY_COMBATANT(i).turn.action_flags.value & COMBATANT_FLAG_PREEMPTIVE_TURN)) {
            if (func_801DB9E4(i) & 0xFF) {
                value = ENEMY_COMBATANT(i).stats.agility;
                sum += value;
                if (max < (u32)value) {
                    max = value;
                }
            }
        }
        i++;
    } while ((u32)i < 11);
    sum = 0;
    i   = 0;
    do {
        if ((D_801463BA == 0) ||
            (g_BattlePartyBattlers[i].turn.action_flags.volatile_value & COMBATANT_FLAG_PREEMPTIVE_TURN)) {
            if (func_801DB844(i) & 0xFF) {
                total        = sum;
                entry        = &entries[total];
                entry->index = (s16)i;
                entry->value = g_BattlePartyBattlers[i].chr.stats.agility;
                sum++;
            }
        }
        i++;
    } while ((u32)i < BATTLE_COMMAND_MAX);
    max   = sum;
    count = sum & 0xFF;
    if (count >= 2) {
        sum = 0;
        if ((count - 1) > 0) {
            i = 1;
            do {
                if ((u32)i < count) {
                    entry      = &entries[sum];
                    scan       = i * 4;
                    scan_index = (u32)i;
                    do {
                        other = &entries[i];
                        if (entry->value < other->value) {
                            temp   = *entry;
                            *entry = *other;
                            *other = temp;
                        }
                        i++;
                        scan       = i * 4;
                        scan_index = (u32)i;
                    } while (scan_index < (u32)max);
                }
                sum++;
                count = max & 0xFF;
                i     = sum + 1;
            } while (sum < (count - 1));
        }
    }
    i = 0;
    do {
        D_801462F6[i] = 0xFF;
        i++;
    } while ((u32)i < BATTLE_COMMAND_MAX);
    cursor  = &g_BattleCommandCount;
    *cursor = 0;
    i       = 0;
    if (max & 0xFF) {
        do {
            if (func_801DB844((u8)entries[i].index) & 0xFF) {
                D_801462F6[*cursor] = (u8)entries[i].index;
                *cursor             = (s8)(*cursor + 1);
            }
            i++;
        } while ((u32)i < (u32)(max & 0xFF));
    }
}
#else
INCLUDE_ASM(func_801DA7D4);
#endif

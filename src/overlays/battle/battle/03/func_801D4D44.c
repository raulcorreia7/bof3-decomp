#include "battle_03.h"

/* advances the battler-local countdown bytes and, when the global suppression countdown expires, clears the
 * shared 0x10 flag across all available battlers. FAKE: each countdown byte is read through a copy; the extra
 * temporary steers global-alloc so the scaled index keeps a0 and the count keeps v1.
 */
MATCH void func_801D4D44(void) {
    u8                     index;
    u32                    clr;
    u32                    enemy_index;
    volatile PartyBattler* local_table;
    volatile EnemyBattler* enemy_table;

    index       = 0u;
    local_table = g_BattlePartyBattlers;
    do {
        if (func_801D64C4(index) == 0u) {
            if ((g_BattlePartyBattlers[index].action_flags.value & 1u) != 0u) {
                u8 loaded = g_BattlePartyBattlers[index].counter_136;
                u8 count  = loaded;
                if (count < 6u) {
                    count += 1u;
                    local_table[index].counter_136 = count;
                }
            }
            if (HAS_STATUS(g_BattlePartyBattlers[index], 0x800u)) {
                u8 loaded = g_BattlePartyBattlers[index].counter_137;
                u8 count  = loaded;
                if (count < 6u) {
                    count += 1u;
                    local_table[index].counter_137 = count;
                }
            }
            if ((g_BattlePartyBattlers[index].action_flags.value & COMBATANT_FLAG_CHARGING) != 0u) {
                u8 loaded = g_BattlePartyBattlers[index].counter_136;
                u8 count  = loaded;
                if (count < 3u) {
                    count += 1u;
                    local_table[index].counter_136 = count;
                }
            }
        }
        index += 1u;
    } while (index < 3u);

    index       = 3u;
    enemy_table = D_801EB630;
    do {
        if (func_801D64C4(index) == 0u) {
            enemy_index = index - 3u;
            if ((D_801EB630[enemy_index].action_flags & COMBATANT_FLAG_CHARGING) != 0u) {
                u8 loaded = D_801EB630[enemy_index].unk_112;
                u8 count  = loaded;
                if (count < 3u) {
                    count += 1u;
                    enemy_table[enemy_index].unk_112 = count;
                }
            }
        }
        index += 1u;
    } while (index < 11u);

    {
        /* FAKE: volatile-drop pointer keeps the countdown cell address
         * in one register across the read and the write. */
        u8* countdown = (u8*)&g_BattleActionLock;
        u8  count     = *countdown;

        if (count != 0u) {
            *countdown = count - 1u;
            if (--count == 0u) {
                index = 0u;
                clr   = 0xFFFFFFEFu;
                do {
                    if (Battle_SlotIsBlocked(index) == 0u) {
                        g_BattlePartyBattlers[index].action_flags.value &= clr;
                    }
                    index += 1u;
                } while (index < 3u);

                index = 3u;
                clr   = 0xFFFFFFEFu;
                do {
                    if (Battle_SlotIsBlocked(index) == 0u) {
                        ENEMY_COMBATANT(index).action_flags &= clr;
                    }
                    index += 1u;
                } while (index < 11u);
            }
        }
    }
}

#include "battle_03.h"

/* advances the battler-local countdown bytes and, when the global suppression countdown expires, clears the
 * shared 0x10 flag across all available battlers. FAKE: each countdown byte is read through a copy; the extra
 * temporary steers global-alloc so the scaled index keeps a0 and the count keeps v1.
 */
/* func_801D4D44 */
MATCH void Battle_TickCountdowns(void) {
    u8                     index;
    u32                    clr;
    u32                    enemy_index;
    volatile PartyMember*  local_table;
    volatile EnemyBattler* enemy_table;

    index       = 0u;
    local_table = g_Game.members;
    do {
        if (Battle_GetActionLock(index) == 0u) {
            if ((g_Game.members[index].u.turn.action_flags.value & COMBATANT_FLAG_DRAGON_FORM_QUEUED) != 0u) {
                u8 loaded = g_Game.members[index].counter_136;
                u8 count  = loaded;
                if (count < 6u) {
                    count += 1u;
                    local_table[index].counter_136 = count;
                }
            }
            if (HAS_STATUS(g_Game.members[index], 0x800u)) {
                u8 loaded = g_Game.members[index].counter_137;
                u8 count  = loaded;
                if (count < 6u) {
                    count += 1u;
                    local_table[index].counter_137 = count;
                }
            }
            if ((g_Game.members[index].u.turn.action_flags.value & COMBATANT_FLAG_CHARGING) != 0u) {
                u8 loaded = g_Game.members[index].counter_136;
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
    enemy_table = g_BattleEnemyBattlers;
    do {
        if (Battle_GetActionLock(index) == 0u) {
            enemy_index = index - 3u;
            if ((g_BattleEnemyBattlers[enemy_index].turn.action_flags.value & COMBATANT_FLAG_CHARGING) != 0u) {
                u8 loaded = g_BattleEnemyBattlers[enemy_index].unk_112;
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
        u8* countdown = (u8*)&g_Battle.action_lock;
        u8  count     = *countdown;

        if (count != 0u) {
            *countdown = count - 1u;
            if (--count == 0u) {
                index = 0u;
                clr   = 0xFFFFFFEFu;
                do {
                    if (Battle_SlotIsBlocked(index) == 0u) {
                        g_Game.members[index].u.turn.action_flags.value &= clr;
                    }
                    index += 1u;
                } while (index < 3u);

                index = 3u;
                clr   = 0xFFFFFFEFu;
                do {
                    if (Battle_SlotIsBlocked(index) == 0u) {
                        ENEMY_COMBATANT(index).turn.action_flags.value &= clr;
                    }
                    index += 1u;
                } while (index < 11u);
            }
        }
    }
}

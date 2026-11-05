#include "battle_03.h"

/* Current battler slot index (local slots 0-2, enemy slots from 3). */

/* clears paired local/enemy flag bits and associated countdown bytes
 * for the current battler, except under two specific global mode/kind
 * combinations.
 */
MATCH void func_801D4850(void) {
    u32 clr;

    if (((LOBU(g_BattleActionType)) != BATTLE_ACTION_ABILITY) || ((LOHU(g_BattleActionId)) != 0x27u)) {
        if (BATTLER_IS_PLAYER(g_BattleActiveBattler)) {
            {
                u32 flags = BATTLE_ACTIVE_PARTY.flags_128.value & COMBATANT_FLAG_POWER_BOOST;
                clr       = 0xFFFFFFBFu;

                if (flags != 0u) {
                    BATTLE_ACTIVE_PARTY.charge = 0u;
                    BATTLE_ACTIVE_PARTY.flags_128.value &= clr;
                }
            }
        } else {
            {
                u32 flags = ENEMY_COMBATANT(g_BattleActiveBattler).flags_104 & COMBATANT_FLAG_POWER_BOOST;
                clr       = 0xFFFFFFBFu;

                if (flags != 0u) {
                    /* FAKE: retail keeps the enemy index in v1. */
                    MATCH_REG(u32, eindex, "v1");

                    ENEMY_COMBATANT(g_BattleActiveBattler).unk_114 = 0u;
                    eindex                                         = g_BattleActiveBattler;
                    ENEMY_COMBATANT(eindex).flags_104 &= clr;
                }
            }
        }
    }

    if (((LOBU(g_BattleActionType)) != BATTLE_ACTION_ABILITY) || ((LOHU(g_BattleActionId)) != 0xA3u)) {
        if (BATTLER_IS_PLAYER(g_BattleActiveBattler)) {
            {
                u32 flags = BATTLE_ACTIVE_PARTY.flags_128.value & 0x80u;
                clr       = 0xFFFFFF7Fu;

                if (flags != 0u) {
                    BATTLE_ACTIVE_PARTY.unk_139 = 0u;
                    BATTLE_ACTIVE_PARTY.flags_128.value &= clr;
                }
            }
        } else {
            {
                u32 flags = ENEMY_COMBATANT(g_BattleActiveBattler).flags_104 & 0x80u;
                clr       = 0xFFFFFF7Fu;

                if (flags != 0u) {
                    /* FAKE: retail keeps the enemy index in v1. */
                    MATCH_REG(u32, eindex, "v1");

                    ENEMY_COMBATANT(g_BattleActiveBattler).unk_115 = 0u;
                    eindex                                         = g_BattleActiveBattler;
                    ENEMY_COMBATANT(eindex).flags_104 &= clr;
                }
            }
        }
    }
}

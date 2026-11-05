#include "battle_15.h"

/* Non-volatile alias for the battler count at 0x801462F0, read as the player
 * loop bound. FAKE: the volatile read keeps the bound load behind the slot
 * increment, retail loads it first; pure C reached 85.71% with the volatile
 * symbol and 98.06% with the alias.
 */

MATCH void func_8009B2B0(void) {
    u8* counter_byte;
    s32 slot;
    u32 player_sum;
    u32 enemy_sum;
    s32 roll;
    u8  counter;
    u32 divisor;

    counter_byte  = &D_80146326.attempts;
    player_sum    = 0;
    enemy_sum     = 0;
    counter       = *counter_byte + 1;
    *counter_byte = counter;
    if (g_BattleEncounter != 0) {
        g_BattleUiStep = g_BattleUiStep + 1;
    } else if (counter >= 3) {
        g_BattleUiStep = 2;
    } else {
        for (slot = 3; slot < COMBATANT_COUNT; slot++) {
            if (Battle_SlotIsBlocked(slot) == 0) {
                enemy_sum += D_801EB630[slot].stats.agility;
            }
        }
        divisor = g_BattleLivingEnemyCount;
        enemy_sum /= divisor;

        for (slot = 0; slot < (*(u8*)&g_BattlePartyCount); slot++) {
            if (Battle_SlotIsBlocked(slot) == 0) {
                player_sum += g_BattlePartyBattlers[slot].chr.stats.agility;
            }
        }
        player_sum /= g_BattleLivingPartyCount;

        roll = func_8009BACC(player_sum - enemy_sum) & BYTE_MASK;
        if (roll >= (RANDOM_MASK(0x3F))) {
            /* FAKE: keeps roll live across the compare so the slt result takes v0 as in retail; pure C best 98.06%,
             * no source spelling of the compare moves the result register. */
            MATCH_FAKE_USE(roll);
            g_BattleUiStep = 2;
        } else if (g_BattleSurprise == 1) {
            g_BattleUiStep = 2;
        } else {
            g_BattleUiStep = 1;
        }
    }
}

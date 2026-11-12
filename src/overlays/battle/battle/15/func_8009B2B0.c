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

    counter_byte  = &g_Battle.outcome.attempts;
    player_sum    = 0;
    enemy_sum     = 0;
    counter       = *counter_byte + 1;
    *counter_byte = counter;
    if (BATTLE_IS_SCRIPTED()) {
        g_Battle.ui_step = g_Battle.ui_step + 1;
    } else if (counter >= 3) {
        g_Battle.ui_step = 2;
    } else {
        for (slot = 3; slot < COMBATANT_COUNT; slot++) {
            if (Battle_SlotIsBlocked((u8)slot) == 0) {
                enemy_sum += g_BattleEnemyBattlers[slot].stats.agility;
            }
        }
        divisor = g_Battle.living_enemy_count;
        enemy_sum /= divisor;

        for (slot = 0; slot < (*(u8*)&g_Battle.party_count); slot++) {
            if (Battle_SlotIsBlocked((u8)slot) == 0) {
                player_sum += g_Game.members[slot].chr.stats.agility;
            }
        }
        player_sum /= g_Battle.living_party_count;

        roll = func_8009BACC(player_sum - enemy_sum) & BYTE_MASK;
        if (roll >= RANDOM_MASK(0x3F)) {
            /* FAKE: keeps roll live across the compare so the slt result takes v0 as in retail; pure C best 98.06%,
             * no source spelling of the compare moves the result register. */
            FAKE_USE(roll);
            g_Battle.ui_step = 2;
        } else if (g_Battle.outcome.surprise == 1) {
            g_Battle.ui_step = 2;
        } else {
            g_Battle.ui_step = 1;
        }
    }
}

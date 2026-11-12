#include "battle_03.h"

/* Advances battle state, clears the suppression flag on the battler and enemy rows, and updates the scene counter. */

MATCH void func_801D4B38(void) {
    u8  action;
    u8  i;
    u8  slot;
    u8* state;

    state = (u8*)&D_801463BA;
    if (*state == 0 && g_Battle.action_lock == 0) {
        action = func_801DB058();
        switch (action) {
            case 0:
                *state = 0;
                break;
            case 3:
                if (g_Battle.outcome.surprise == 2) {
                    *state = 2;
                    g_Battle.phase.sub_step += 1;
                    return;
                }
                *state = 3;
                g_Battle.phase.sub_step += 1;
                return;
            case 1:
                if (g_Battle.outcome.surprise == 2) {
                    *state = 0;
                    g_Battle.phase.sub_step += 1;
                    break;
                }
                *state = 1;
                g_Battle.phase.sub_step += 1;
                return;
            case 2:
                *state = 2;
                g_Battle.phase.sub_step += 1;
                return;
        }
    }
    for (i = 0; i < 2; i++) {
        g_Game.members[i].u.turn.action_flags.volatile_value &= 0xFFFF7FFF;
    }
    for (slot = 3; slot < 10; slot++) {
        ENEMY_COMBATANT(slot).turn.action_flags.volatile_value &= ~COMBATANT_FLAG_PREEMPTIVE_TURN;
    }
    D_801463BA = 0;
    D_801463D0 += 1;
    Battle_TickCountdowns();
    g_Battle.phase.sub_step = 0;
    g_Battle.phase.step += 1;
}

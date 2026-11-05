#include "battle_03.h"

/* clears the current enemy's deferred halfword, resets the local work point pair, runs the mirror helper,
 * selects local work mode 4, runs the battle update, posts event 0x205 and advances the local substate.
 */
MATCH void func_801E44D4(void) {
    PartyBattler* work;

    work                                = g_Task;
    BATTLE_CURRENT_ENEMY_PTR->hp_change = 0;
    work->unk_0C                        = -0x2000;
    work->unk_10                        = 0;
    func_801DD350((s32)work);
    g_Task->timer = 4;
    func_801E30F8();
    SND_PlayCue(EMI_CUE_ID(2, 5));
    g_Task->unk_03 += 1;
}

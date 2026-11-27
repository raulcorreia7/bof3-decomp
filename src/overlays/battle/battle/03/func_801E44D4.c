#include "battle_03.h"

/* clears the current enemy's deferred halfword, resets the local work point pair, runs the mirror helper,
 * selects local work mode 4, runs the battle update, posts event 0x205 and advances the local substate.
 */
MATCH void func_801E44D4(void) {
    PartyMember* work;

    work                                     = SELF(PartyMember);
    BATTLE_CURRENT_ENEMY_PTR->turn.hp_change = 0;
    work->unk_0C                             = -0x2000;
    work->unk_10                             = 0;
    Effect_RotatePosition(work);
    SELF(PartyMember)->timer = 4;
    Battle_IsEnemyBlocked();
    SND_SEPlay(EMI_SE_ID(SND_BANK_AREA, 5));
    SELF(PartyMember)->unk_03 += 1;
}

#include "battle_03.h"

/* clears local work flag 0x40, selects enemy mode 0, then resets the
 * local work timers and counters and enters substate 1.
 */
MATCH void func_801E3334(void) {
    PartyMember* work;

    SELF(PartyMember)->header.flags &= ~ACTOR_FLAG_HIDDEN;
    Battle_RequestEnemyScript(0);
    work          = SELF(PartyMember);
    work->unk_48  = 2u;
    work          = SELF(PartyMember);
    work->unk_18  = 0x666u;
    work->scale.y = 0u;
    work->scale.x = 0u;
    work->unk_0C  = 0u;
    work->unk_03  = 1u;
}

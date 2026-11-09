#include "battle_03.h"

/* clears local work flag 0x40, selects enemy mode 0, then resets the
 * local work timers and counters and enters substate 1.
 */
MATCH void func_801E3334(void) {
    PartyMember* work;

    g_Task->header.flags &= ~ACTOR_FLAG_HIDDEN;
    func_801E2314(0);
    work          = g_Task;
    work->unk_48  = 2u;
    work          = g_Task;
    work->unk_18  = 0x666u;
    work->scale.y = 0u;
    work->scale.x = 0u;
    work->unk_0C  = 0u;
    work->unk_03  = 1u;
}

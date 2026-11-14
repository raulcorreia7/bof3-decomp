#include "battle_03.h"

/* runs the battle step routine Battle_IsEnemyBlockedOnce, then increments the
 * counter at offset 0x02 of the battle work record held in the scratchpad
 * pointer cell at 0x1F800044.
 */
MATCH void func_801E4DD8(void) {
    PartyMember* work;

    Battle_IsEnemyBlockedOnce();
    work = g_Task;
    work->header.step += 1;
}

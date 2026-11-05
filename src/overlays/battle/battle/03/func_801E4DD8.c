#include "battle_03.h"

/* runs the battle step routine func_801E3160, then increments the
 * counter at offset 0x02 of the battle work record held in the scratchpad
 * pointer cell at 0x1F800044.
 */
MATCH void func_801E4DD8(void) {
    PartyBattler* work;

    func_801E3160();
    work = g_Task;
    work->step += 1;
}

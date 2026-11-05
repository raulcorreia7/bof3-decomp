#include "battle_03.h"

/* calls the battle-readiness helper func_801DEE4C, then increments
 * byte +0x02 of the current local-work block selected by the scratchpad
 * pointer cell at 0x1F800044.
 */
MATCH void func_801E19DC(void) {
    PartyBattler* work;

    func_801DEE4C();
    work = g_Task;
    work->step += 1;
}

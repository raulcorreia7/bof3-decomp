#include "battle_03.h"

/* calls the battle-readiness helper Battle_IsPartyMemberBlocked, then increments
 * byte +0x02 of the current local-work block selected by the scratchpad
 * pointer cell at 0x1F800044.
 */
MATCH void func_801E19DC(void) {
    PartyMember* work;

    Battle_IsPartyMemberBlocked();
    work = g_Task;
    work->header.step += 1;
}

#include "battle_03.h"

/* refreshes the active local work, then runs the 0x10-priority or
 * the 0x20-priority battle handler according to the +0x124 flags.
 */
MATCH void func_801E1C78(void) {
    volatile PartyBattler* work;
    u32                    flags;

    func_801DF34C();
    work  = g_GameState;
    flags = work->damage_flags.value;
    if ((flags & 0x10u) != 0u) {
        func_801DEDE4();
    } else if ((flags & 0x20u) != 0u) {
        func_801DEE4C();
    }
}

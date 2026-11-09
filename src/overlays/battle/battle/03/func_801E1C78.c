#include "battle_03.h"

/* refreshes the active local work. */
MATCH void func_801E1C78(void) {
    volatile PartyMember* work;
    u32                   flags;

    func_801DF34C();
    work  = g_Game.current;
    flags = work->u.turn.damage_flags.value;
    if ((flags & 0x10u) != 0u) {
        func_801DEDE4();
    } else if ((flags & 0x20u) != 0u) {
        func_801DEE4C();
    }
}

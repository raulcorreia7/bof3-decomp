#include "battle_03.h"

/* runs the battle step routine func_801E3160. */
MATCH void func_801E4DD8(void) {
    PartyMember* work;

    func_801E3160();
    work = g_Task;
    work->header.step += 1;
}

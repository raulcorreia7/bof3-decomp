#include "battle_03.h"

/* calls the battle-readiness helper func_801DEE4C. */
MATCH void func_801E19DC(void) {
    PartyMember* work;

    func_801DEE4C();
    work = g_Task;
    work->header.step += 1;
}

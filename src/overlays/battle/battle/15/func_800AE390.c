#include "battle_15.h"

MATCH void func_800AE390(void) {
    PartyMember* work;

    BATTLE_WORK->unk_09 = 0;
    work                = (PartyMember*)g_Task;
    work->header.mode   = (work->header.mode + 1);
}

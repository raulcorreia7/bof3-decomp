#include "battle_03.h"

MATCH void func_801E06EC(void) {
    volatile PartyMember* work = g_Task;
    volatile PartyMember* battle_work;

    work->unk_03 += 1;
    battle_work = g_Game.current;
    if (!HAS_STATUS(*battle_work, STATUS_PARALYZED)) {
        func_801DEFE4();
    }
}

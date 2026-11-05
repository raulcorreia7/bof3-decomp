#include "battle_03.h"

MATCH void func_801E06EC(void) {
    volatile PartyBattler* work = g_Task;
    volatile PartyBattler* battle_work;

    work->unk_03 += 1;
    battle_work = g_GameState;
    if (!HAS_STATUS(*battle_work, STATUS_PARALYZED)) {
        func_801DEFE4();
    }
}

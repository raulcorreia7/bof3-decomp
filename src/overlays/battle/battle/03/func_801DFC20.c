#include "battle_03.h"

MATCH void func_801DFC20(void) {
    volatile PartyBattler* work;
    PartyBattler*          scratch_work;

    g_GameState->turn.unk_0B = g_Task->unk_4B;
    scratch_work             = g_Task;
    work                     = g_GameState;
    work->unk_134            = scratch_work->unk_58;
    scratch_work->unk_04     = 0;
    g_Task->header.step      = 1;
}

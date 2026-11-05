#include "battle_03.h"

MATCH void func_801E1DD4(void) {
    volatile PartyBattler* work;

    g_Task->mode   = 2;
    g_Task->step   = 0;
    g_Task->unk_03 = 0;
    g_Task->unk_04 = 0;
    Battle_ClearSlotPending(g_Task->slot);
    work = g_GameState;
    BATTLE_LOCAL_WORD_124(work) &= ~0x200u;
    if ((g_BattleState & BATTLE_STATE_REPRISAL_PENDING) == 0u) {
        BATTLE_LOCAL_BYTE_119(work) = 0;
    }
}

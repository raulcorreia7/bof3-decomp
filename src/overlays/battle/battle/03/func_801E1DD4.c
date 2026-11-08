#include "battle_03.h"

MATCH void func_801E1DD4(void) {
    volatile PartyMember* work;

    g_Task->header.mode = 2;
    g_Task->header.step = 0;
    g_Task->unk_03      = 0;
    g_Task->unk_04      = 0;
    Battle_ClearSlotPending(g_Task->slot);
    work = g_Game.current;
    BATTLE_LOCAL_WORD_124(work) &= ~0x200u;
    if ((g_Battle.state & BATTLE_STATE_REPRISAL_PENDING) == 0u) {
        BATTLE_LOCAL_BYTE_119(work) = 0;
    }
}

#include "battle_03.h"

MATCH void func_801E1DD4(void) {
    volatile PartyMember* work;

    g_Task->header.mode = 2;
    g_Task->header.step = 0;
    g_Task->unk_03      = 0;
    g_Task->unk_04      = 0;
    Battle_ClearSlotPending(g_Task->slot);
    work = g_Game.current;
    work->u.turn.damage_flags.volatile_value &= ~0x200u;
    if ((g_Battle.state & BATTLE_STATE_REPRISAL_PENDING) == 0u) {
        work->u.turn.command.type = 0;
    }
}

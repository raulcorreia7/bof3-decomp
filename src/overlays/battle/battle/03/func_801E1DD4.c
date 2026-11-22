#include "battle_03.h"

MATCH void func_801E1DD4(void) {
    volatile PartyMember* work;

    TASK(PartyMember)->header.mode = 2;
    TASK(PartyMember)->header.step = 0;
    TASK(PartyMember)->unk_03      = 0;
    TASK(PartyMember)->unk_04      = 0;
    Battle_ClearSlotPending(TASK(PartyMember)->slot);
    work = g_Game.current;
    work->u.turn.damage_flags.volatile_value &= ~0x200u;
    if ((g_Battle.flags & BATTLE_STATE_REPRISAL_PENDING) == 0u) {
        work->u.turn.command.type = 0;
    }
}

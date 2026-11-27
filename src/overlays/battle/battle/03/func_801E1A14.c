#include "battle_03.h"

MATCH void func_801E1A14(void) {
    volatile PartyMember* work;
    u16*                  battle_flags;
    u32                   expected;

    expected = 4;
    work     = g_Game.current;
    if (work->u.turn.command.type == expected) {
        work->chr.ap = work->chr.ap - g_Battle.unk_E8;
    }
    battle_flags = &g_Battle.flags;
    *battle_flags |= 0x800;
    g_Game.current->u.turn.command.type = 0;
    if ((D_801CA71C[g_Battle.action_id].mask & 0x800u) != 0u) {
        SELF(PartyMember)->header.step += 1;
    } else {
        Battle_IsPartyMemberBlocked();
        SELF(PartyMember)->header.step = 4;
    }
}

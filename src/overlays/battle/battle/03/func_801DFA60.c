#include "battle_03.h"

MATCH void func_801DFA60(void) {
    PartyMember* work;
    u16*         gate;
    u8           count;
    u8           chance;

    Battle_IsPartyMemberBlocked();
    work         = g_Task;
    count        = work->unk_09 - 1;
    work->unk_09 = count;
    if (count == 0) {
        if ((func_800A8F58() & BYTE_MASK) == 0) {
            chance = g_Game.current->chr.stats.critical_chance;
            if ((RANDOM_PERCENT()) < chance) {
                gate = &g_Battle.state;
                *gate |= 0x80;
                func_801DD858(3);
            } else {
                func_801DD858(2);
            }
        } else {
            func_801DD858(3);
        }
        func_801DD858(4);
        g_Task->header.step = g_Task->header.step + 1;
    }
}

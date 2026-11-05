#include "battle_03.h"

MATCH void func_801E1A14(void) {
    volatile PartyBattler* work;
    u16*                   battle_flags;
    u32                    expected;

    expected = 4;
    work     = g_GameState;
    if (work->mode_119 == expected) {
        work->stats.current_ap = work->stats.current_ap - D_801463C8;
    }
    battle_flags = &g_BattleState;
    *battle_flags |= 0x800;
    g_GameState->mode_119 = 0;
    if ((D_801CA71C[g_BattleActionId].mask & 0x800u) != 0u) {
        g_Task->step += 1;
    } else {
        func_801DEE4C();
        g_Task->step = 4;
    }
}

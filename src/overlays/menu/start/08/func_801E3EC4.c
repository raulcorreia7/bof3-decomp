#include "start_08.h"

MATCH void func_801E3EC4(void) {
    u8* hint;
    u8* work;
    u8* tail;

    hint            = &g_EmiLoadedCharacterIndex;
    g_GameFlags     = 0;
    g_AreaWalkFlags = 0;
    *hint           = 0;
    g_GameState     = g_BattlePartyBattlers;
    g_SpadWork      = (u8*)g_BattlePartyBattlers;
    func_801C1254(0, 0);
    g_SpadWork[0]              = 1;
    g_GameState->slot_index_79 = 0;
    work                       = g_SpadWork;
    work[0x29]                 = 0;
    tail                       = g_SpadWork;
    FIELD(s16, work, 0x2Eu)    = 0x10A;
    FIELD(s16, work, 0x30u)    = 0x51;
    tail[0x48]                 = 0;
    g_SpadWork[9]              = 1;
    g_SpadWork[0x24]           = 0x81;
    g_SpadWork[6]              = 4;
    g_SpadWork[9]              = 0;
    Actor_SelectScript((g_SpadWork[6] + 8) & BYTE_MASK);
    D_801ED7EC      = 1;
    *hint           = 0xFF;
    D_801ED864      = 0x80;
    D_80148694      = 0;
    D_801ED868      = 0x40;
    g_MenuStartStep = 0;
    /* FAKE: retail takes the step counter's address before the increment. */
    (*(CampMenuStepCounter*)&g_GameEntrySubstate).rows[0] += 1;
}

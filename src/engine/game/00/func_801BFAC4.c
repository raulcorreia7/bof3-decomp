#include "game_00.h"

MATCH void func_801BFAC4(void) {
    u8* work;
    s32 i;

    i = 0;
    while (i < g_PartySize) {
        work        = (u8*)g_Game.members + i * BATTLE_PARTY_STRIDE;
        g_GameState = work;
        TASK_SET(work);
        Actor_StepAnimLoop();
        i++;
    }
}

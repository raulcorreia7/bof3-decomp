#include "game_00.h"

MATCH void func_801AD184(void) {
    if (!ACTOR_IN_USE(g_ActorSlots[g_Task->param.unk_0B])) {
        sprintf(&g_TextVariables[0], &D_80195F0C, 5);
        Resource_RequestArea(5);
        g_GameStateIndex = GAME_REQUEST_MESSAGE;
        g_Task->unk_04   = 4;
    }
}

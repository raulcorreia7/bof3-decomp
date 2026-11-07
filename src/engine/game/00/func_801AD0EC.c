#include "game_00.h"

MATCH void func_801AD0EC(void) {
    s32 ui_state;

    ui_state = GAME_REQUEST_MESSAGE;
    if (!ACTOR_IN_USE(g_ActorSlots[g_Task->param.unk_0B])) {
        sprintf(&g_TextVariables[0], &D_80195F0C, 2);
        Resource_RequestArea(5);
        g_GameStateIndex = ui_state;
        g_Task->unk_04   = 4;
    }
}

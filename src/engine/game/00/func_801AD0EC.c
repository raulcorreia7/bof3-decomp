#include "game_00.h"

MATCH void func_801AD0EC(void) {
    s32 ui_mode;

    ui_mode = GAME_REQUEST_MESSAGE;
    if (!ACTOR_IN_USE(g_SpawnedActors[g_Task->param.actor_slot])) {
        TEXT_Format(&g_TextVariables[0], D_80195F0C, 2);
        Message_Request(MSG_005);
        g_GameStateIndex = ui_mode;
        g_Task->unk_04   = 4;
    }
}

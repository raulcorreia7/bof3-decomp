#include "game_00.h"

MATCH void func_801AD90C(void) {
    u8     msgId;
    Actor* spad;

    spad = g_Task;
    if (!ACTOR_IN_USE(g_ActorSlots[spad->param.unk_0B])) {
        msgId = s_SceneMessages[spad->unk_04];
        if (msgId != 0) {
            sprintf(&g_TextVariables[0], &D_80195F0C, msgId);
            Resource_RequestArea(5);
            g_GameStateIndex = GAME_REQUEST_MESSAGE;
            g_Task->unk_04   = 4U;
            return;
        }
        spad->unk_04 = 5U;
    }
}

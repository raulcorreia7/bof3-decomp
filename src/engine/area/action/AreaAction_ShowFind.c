#include "engine/game/00/game_00.h"

/* func_801AD90C */
MATCH void AreaAction_ShowFind(void) {
    u8     msgId;
    Actor* spad;

    spad = g_Task;
    if (!ACTOR_IN_USE(g_SpawnedActors[spad->param.actor_slot])) {
        msgId = g_FindZenny[spad->unk_04];
        if (msgId != 0) {
            TEXT_Format(&g_TextVariables[0], D_80195F0C, msgId);
            Message_Request(MSG_SYSTEM_FOUND_ZENNY);
            g_GameStateIndex = GAME_REQUEST_MESSAGE;
            g_Task->unk_04   = 4U;
            return;
        }
        spad->unk_04 = 5U;
    }
}

#include "engine/game/00/game_00.h"

/* func_801AD90C */
MATCH void AreaAction_ShowFind(void) {
    u8     msgId;
    Actor* spad;

    spad = SELF(Actor);
    if (!ACTOR_IN_USE(g_SpawnedActors[spad->param.actor_slot])) {
        msgId = g_FindZenny[spad->unk_04];
        if (msgId != 0) {
            TEXT_Format(&g_TextVariables[0], D_80195F0C, msgId);
            UI_MessageRequest(MSG_SYSTEM_FOUND_ZENNY);
            g_SysThreads[0].tail.game_entry.request = GAME_REQUEST_MESSAGE;
            SELF(Actor)->unk_04                     = 4U;
            return;
        }
        spad->unk_04 = 5U;
    }
}

#include "engine/game/00/game_00.h"

/* func_801AD184 */
MATCH void AreaAction_FindLarge(void) {
    if (!ACTOR_IN_USE(g_SpawnedActors[g_Task->param.actor_slot])) {
        TEXT_Format(&g_TextVariables[0], D_80195F0C, 5);
        Message_Request(MSG_SYSTEM_FOUND_ZENNY);
        g_GameStateIndex = GAME_REQUEST_MESSAGE;
        g_Task->unk_04   = 4;
    }
}

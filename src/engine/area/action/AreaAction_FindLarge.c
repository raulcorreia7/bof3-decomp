#include "engine/game/00/game_00.h"

/* func_801AD184 */
MATCH void AreaAction_FindLarge(void) {
    if (!ACTOR_IN_USE(g_SpawnedActors[SELF(Actor)->param.actor_slot])) {
        TEXT_Format(&g_TextVariables[0], D_80195F0C, 5);
        UI_MessageRequest(MSG_SYSTEM_FOUND_ZENNY);
        g_SysThreads[0].tail.game_entry.request = GAME_REQUEST_MESSAGE;
        SELF(Actor)->unk_04                     = 4;
    }
}

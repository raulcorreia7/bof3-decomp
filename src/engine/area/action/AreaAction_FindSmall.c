#include "engine/game/00/game_00.h"

/* func_801AD0EC */
MATCH void AreaAction_FindSmall(void) {
    s32 ui_mode;

    ui_mode = GAME_REQUEST_MESSAGE;
    if (!ACTOR_IN_USE(g_SpawnedActors[SELF(Actor)->param.actor_slot])) {
        TEXT_Format(&g_TextVariables[0], D_80195F0C, 2);
        UI_MessageRequest(MSG_SYSTEM_FOUND_ZENNY);
        g_SysThreads[0].tail.game_entry.request = ui_mode;
        SELF(Actor)->unk_04                     = 4;
    }
}

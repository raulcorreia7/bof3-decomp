#include "area189_13.h"
#include "area/map.h"

MATCH void func_801F4D14(void) {
    u8* flags;

    if (g_GameStateIndex != GAME_REQUEST_MESSAGE) {
        Game_ClearScriptActive();
        flags  = &g_ScenarioState.flags_01;
        *flags = *flags & 0xFE;
        if (g_SceneEventState.step != 0) {
            Game_RequestAreaChange(AREA_ID_OASIS, TO_COORD(24), TO_COORD(48), FACING_UP);
        } else {
            Game_RequestAreaChange(AREA_ID_DESERT_ENTRANCE_CAMP, TO_COORD(26) + COORD_HALF, TO_COORD(28), FACING_UP);
        }
        g_SceneEventState.mode = SCENE_EVENT_NONE;
        g_SceneEventState.step = 0;
    }
}

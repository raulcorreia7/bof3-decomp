#include "area098_13.h"
#include "area/map.h"

MATCH void func_801F5E1C(void) {
    s8* flag;

    flag = &g_SceneEventStep;
    if (*flag == 0 && g_GameStateIndex != GAME_REQUEST_MESSAGE) {
        D_80145040 = g_Game.members[0].pos.x.fixed;
        D_80145044 = g_Game.members[0].pos.y.fixed;
        D_80145048 = g_GameAreaId;
        Game_RequestAreaChange(AREA_ID_DEIS_ROOM, TO_COORD(56), TO_COORD(44), FACING_UP);
        Game_ClearScriptActive();
        g_SceneEventMode = SCENE_EVENT_NONE;
        *flag            = 0;
    }
}

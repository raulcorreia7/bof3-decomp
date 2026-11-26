#include "area098_13.h"
#include "menu/save_data.h"
#include "area/map.h"

MATCH void func_801F5E1C(void) {
    s8* flag;

    flag = &g_SceneEventState.step;
    if (*flag == 0 && g_GameStateIndex != GAME_REQUEST_MESSAGE) {
        g_SaveData.return_point.x       = g_Game.members[0].pos.x.fixed;
        g_SaveData.return_point.y       = g_Game.members[0].pos.y.fixed;
        g_SaveData.return_point.area_id = g_GameAreaId;
        Game_RequestAreaChange(AREA_ID_DEIS_ROOM, TO_COORD(56), TO_COORD(44), FACING_UP);
        Game_ClearScriptActive();
        g_SceneEventState.mode = SCENE_EVENT_NONE;
        *flag                  = 0;
    }
}

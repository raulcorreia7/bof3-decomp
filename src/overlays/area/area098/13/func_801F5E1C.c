#include "area098_13.h"
#include "area/map.h"

MATCH void func_801F5E1C(void) {
    s8* flag;

    flag = &g_SceneEventStep;
    if (*flag == 0 && g_GameStateIndex != GAME_REQUEST_MESSAGE) {
        D_80145040 = D_80145EC4[0];
        D_80145044 = D_80145EC8;
        D_80145048 = g_GameAreaId;
        Game_RequestAreaChange(AREA_ID_DEIS_ROOM, 0x380000, 0x2C0000, 1);
        Game_ClearScriptActive();
        g_SceneEventMode = 0;
        *flag            = 0;
    }
}

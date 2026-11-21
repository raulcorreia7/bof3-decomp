#include "engine/game/00/game_00.h"

/* func_80198B6C */
MATCH void Game_EndSceneCamera(void) {
    Game_EaseCameraToRest();
    Game_RunSceneFrame();
    if ((g_AreaCameraAngle.vx == -0x2AA) && (g_AreaCameraAngle.vz == 512)) {
        g_GameEntrySubstate = 0;
    }
}

#include "engine/game/00/game_00.h"

/* func_801981D4 */
MATCH void Game_CameraLookEnd(void) {
    Game_EaseCameraToRest();
    if (g_AreaCameraAngle.vx == -682 && g_AreaCameraAngle.vz == ANGLE_45) {
        g_SysThreads[0].tail.game_entry.request  = GAME_REQUEST_IDLE;
        g_SysThreads[0].tail.game_entry.state    = GAME_MODE_FIELD;
        g_SysThreads[0].tail.game_entry.substate = 0;
    }
}

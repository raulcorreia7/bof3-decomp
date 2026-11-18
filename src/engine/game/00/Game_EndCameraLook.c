#include "game_00.h"

/* func_801981D4 */
MATCH void Game_EndCameraLook(void) {
    Game_EaseCameraToRest();
    if (g_AreaCameraAngle.vx == -682 && g_AreaCameraAngle.vz == ANGLE_45) {
        g_GameStateIndex    = GAME_REQUEST_IDLE;
        g_GameEntryState    = GAME_MODE_FIELD;
        g_GameEntrySubstate = 0;
    }
}

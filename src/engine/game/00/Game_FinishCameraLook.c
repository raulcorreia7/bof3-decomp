#include "game_00.h"

/* func_801981D4 */
MATCH void Game_FinishCameraLook(void) {
    func_801990D0();
    if (g_AreaCameraAngle.vx == -682 && g_AreaCameraAngle.vz == ANGLE_45) {
        g_GameStateIndex    = GAME_REQUEST_IDLE;
        g_GameEntryState    = GAME_STATE_FIELD;
        g_GameEntrySubstate = 0;
    }
}

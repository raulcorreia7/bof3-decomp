#include "engine/game/00/game_00.h"

/* func_8019A8B4 */
/* Runs the pan mode of the current type 0x13 actor, then asks for two camera refreshes. */
MATCH void Camera_PanAngleRun(void) {
    g_CameraAnglePanModes[TASK(Actor)->header.mode]();
    g_AreaCameraRefreshCount = 2;
}

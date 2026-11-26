#include "engine/game/00/game_00.h"

/* func_8019AC34 */
/* Runs the pan mode of the current type 0x31 actor, then asks for two camera refreshes. */
MATCH void Camera_PanZoomRun(void) {
    g_CameraZoomPanModes[TASK(Actor)->header.mode]();
    g_AreaCameraRefreshCount = 2;
}

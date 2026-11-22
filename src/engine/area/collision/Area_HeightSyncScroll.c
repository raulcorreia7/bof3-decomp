#include "engine/slus/slus.h"

/* forwards the actor height span_3E to the scroll recorder while the mode flag
 * g_AreaCameraMoving is clear.
 */
MATCH void Area_HeightSyncScroll(void) {
    if (g_AreaCameraMoving == 0) {
        Area_ScrollAdvance(COORD_INT(g_Game.current->pos.z));
        g_SysThreads[0].tail.game_entry.request = GAME_REQUEST_IDLE;
    }
}

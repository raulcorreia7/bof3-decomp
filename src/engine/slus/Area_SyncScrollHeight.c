#include "engine/slus/slus.h"

/* forwards the actor height span_3E to the scroll recorder while the mode flag
 * g_AreaCameraMoving is clear.
 */
MATCH void Area_SyncScrollHeight(void) {
    if (g_AreaCameraMoving == 0) {
        Area_AdvanceScroll(g_GameState->word_3C.half.span_3E);
        g_GameStateIndex = GAME_REQUEST_IDLE;
    }
}

#include "engine/slus/slus.h"

/* stages the shared mode byte g_AreaDrawMode into the work-area state
 * byte at +0x29, then runs the work-area update at Area_AddGridActor.
 */
MATCH void Area_SetDrawMode(void) {
    Actor* work;

    work             = SELF(Actor);
    work->draw_layer = g_AreaDrawMode;
    Area_AddGridActor();
}

#include "engine/slus/slus.h"

/* stages the shared mode byte g_AreaDrawMode into the work-area state
 * byte at +0x29, then runs the work-area update at func_8014D290.
 */
MATCH void Area_SetDrawMode(void) {
    Actor* work;

    work         = g_SpadWork;
    work->unk_29 = g_AreaDrawMode;
    func_8014D290();
}

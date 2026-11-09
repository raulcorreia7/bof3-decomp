#include "engine/slus/slus.h"

/* stages the shared mode byte g_AreaDrawMode into the work-area state byte at +0x29. */
MATCH void Area_SetDrawMode(void) {
    Actor* work;

    work             = g_Task;
    work->draw_layer = g_AreaDrawMode;
    func_8014D290();
}

#include "area052_13.h"

/* func_801F3980 */
MATCH s32 Area_GetCursor(s32* x, s32* y) {
    Actor* actor = g_Task;
    s32    y_half;

    *x     = actor->pos.x.fixed - COORD_HALF;
    y_half = actor->pos.y.fixed - COORD_HALF;
    *y     = y_half;
    if (g_GameStateIndex == GAME_REQUEST_AREA_CHANGE) {
        func_801F3C4C(*x, y_half);
    }
    if (D_80146867 == 0) {
        g_ScriptState->cursor -= 2;
        return 0;
    }
    return 1;
}

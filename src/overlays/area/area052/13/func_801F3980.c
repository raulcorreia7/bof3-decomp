#include "area052_13.h"

MATCH s32 func_801F3980(s32* x, s32* y) {
    Actor* actor = g_SpadWork;
    s32    y_half;

    *x     = actor->x.fixed - 0x8000;
    y_half = actor->y.fixed - 0x8000;
    *y     = y_half;
    if (g_GameStateIndex == 5) {
        func_801F3C4C(*x, y_half);
    }
    if (D_80146867 == 0) {
        g_ScriptState->cursor -= 2;
        return 0;
    }
    return 1;
}

#include "area106_13.h"

MATCH void func_801F3A60(void) {
    s16 odd;
    s32 row;

    odd = SYS_TestFlag(g_SceneEventFlags, 0x52) != 0;
    if (SYS_TestFlag(g_SceneEventFlags, 0x53) == 0) {
        row = odd;
    } else {
        row = odd | 2;
    }

    SELF(Actor)->pos.x.fixed = TO_COORD(D_801F4850[row].x) | COORD_HALF;
    SELF(Actor)->pos.y.fixed = TO_COORD(D_801F4850[row].y) | COORD_HALF;
    if (SYS_TestFlag(g_SceneEventFlags, 0x4F) != 0) {
        COORD_INT(SELF(Actor)->pos.z) = 2128;
        g_ScriptState->cursor += 8;
    } else {
        COORD_INT(SELF(Actor)->pos.z) = 640;
        g_ScriptState->cursor += row * 2;
    }
}

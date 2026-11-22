#include "area106_13.h"

MATCH void func_801F3A60(void) {
    s32 index;
    s16 odd;
    s32 row;

    odd = SYS_TestFlag(g_SceneEventFlags, 0x52) != 0;
    if (SYS_TestFlag(g_SceneEventFlags, 0x53) == 0) {
        row = odd;
    } else {
        row = odd | 2;
    }
    index = row << 1;

    TASK(Actor)->pos.x.fixed = TO_COORD(D_801F4850[index]) | COORD_HALF;
    TASK(Actor)->pos.y.fixed = TO_COORD(D_801F4851[index]) | COORD_HALF;
    if (SYS_TestFlag(g_SceneEventFlags, 0x4F) != 0) {
        COORD_INT(TASK(Actor)->pos.z) = 2128;
        g_ScriptState->cursor += 8;
    } else {
        COORD_INT(TASK(Actor)->pos.z) = 640;
        g_ScriptState->cursor += index;
    }
}

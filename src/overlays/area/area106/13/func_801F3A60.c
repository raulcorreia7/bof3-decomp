#include "area106_13.h"

MATCH void func_801F3A60(void) {
    s32 slot;
    s16 low;

    low  = SYS_TestFlag(g_SceneEventFlags, 0x52) != 0;
    slot = SYS_TestFlag(g_SceneEventFlags, 0x53);
    if (slot == 0) {
        slot = low;
    } else {
        slot = low | 2;
    }

    TASK(Actor)->pos.x.fixed = TO_COORD(D_801F4850[slot].x) | COORD_HALF;
    TASK(Actor)->pos.y.fixed = TO_COORD(D_801F4850[slot].y) | COORD_HALF;
    if (SYS_TestFlag(g_SceneEventFlags, 0x4F) != 0) {
        COORD_INT(TASK(Actor)->pos.z) = 2128;
        g_ScriptState->cursor += 8;
    } else {
        COORD_INT(TASK(Actor)->pos.z) = 640;
        g_ScriptState->cursor += slot * 2;
    }
}

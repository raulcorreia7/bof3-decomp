#include "area106_13.h"

#ifdef NON_MATCHING
NON_MATCHING void func_801F3A60(void) {
    s32 index;

    index = SYS_TestFlag(g_SceneEventFlags, 0x52) != 0;
    if (SYS_TestFlag(g_SceneEventFlags, 0x53) != 0) {
        index |= 2;
    }
    index <<= 1;

    ((Actor*)g_Task)->pos.x.fixed = TO_COORD(D_801F4850[index]) | COORD_HALF;
    ((Actor*)g_Task)->pos.y.fixed = TO_COORD(D_801F4851[index]) | COORD_HALF;
    if (SYS_TestFlag(g_SceneEventFlags, 0x4F) != 0) {
        COORD_INT(((Actor*)g_Task)->pos.z) = 2128;
        g_ScriptState->cursor += 8;
    } else {
        COORD_INT(((Actor*)g_Task)->pos.z) = 640;
        g_ScriptState->cursor += index;
    }
}
#else
INCLUDE_ASM(func_801F3A60);
#endif

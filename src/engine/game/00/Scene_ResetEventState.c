#include "game_00.h"

MATCH void Scene_ResetEventState(void) {
    s32 i;
    s32 index;
    u8  value;

    i             = 0;
    D_801448E8    = 0;
    D_801448EA[0] = 1;
    D_801448EB    = 0;
    D_801448EC    = 0;
    D_801448EE    = 0;
    D_801448ED    = 0;
    D_801448E9    = 0;
    D_801448F0    = 0;
    do {
        index = i & BYTE_MASK;
        value = s_EventFlagsReset[index];
        i += 1;
        *(&g_SceneEventFlags[0] + index) = value;
    } while ((u32)(i & BYTE_MASK) < 16U);
}

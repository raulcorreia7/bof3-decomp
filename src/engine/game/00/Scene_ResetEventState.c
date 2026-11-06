#include "game_00.h"

MATCH void Scene_ResetEventState(void) {
    s32 i;
    s32 index;
    u8  value;

    i                     = 0;
    D_801448E8            = 0;
    D_801448EA[0]         = 1;
    g_SceneEventMode      = SCENE_EVENT_NONE;
    g_SceneEventStep      = 0;
    D_801448EE            = 0;
    g_SceneEventSelection = 0;
    D_801448E9            = 0;
    D_801448F0            = 0;
    do {
        index = i & BYTE_MASK;
        value = s_EventFlagsReset[index];
        i += 1;
        *(&g_SceneEventFlags[0] + index) = value;
    } while ((i & BYTE_MASK) < 16U);
}

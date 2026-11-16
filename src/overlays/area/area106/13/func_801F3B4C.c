#include "area106_13.h"

MATCH void func_801F3B4C(void) {
    u8* step;

    switch (g_SceneEventState.step) {
        case 0:
            Scene_SetupParty(0);
            step                   = &g_SceneEventState.mode;
            *step                  = SCENE_EVENT_NONE;
            g_SceneEventState.step = 0;
            SYS_SetFlag(step + 0x63D, 0x51);
            break;
        case 2:
            Scene_SetupParty(1);
            step                   = &g_SceneEventState.mode;
            *step                  = SCENE_EVENT_NONE;
            g_SceneEventState.step = 0;
            SYS_ClearFlag(step + 0x63D, 0x51);
            break;
        case 10:
            Scene_SetupParty(2);
            step                   = &g_SceneEventState.mode;
            *step                  = SCENE_EVENT_NONE;
            g_SceneEventState.step = 0;
            SYS_SetFlag(step + 0x63D, 0x52);
            SYS_ClearFlag(step + 0x63D, 0x53);
            break;
        case 12:
            Scene_SetupParty(3);
            step                   = &g_SceneEventState.mode;
            *step                  = SCENE_EVENT_NONE;
            g_SceneEventState.step = 0;
            SYS_ClearFlag(step + 0x63D, 0x52);
            SYS_SetFlag(step + 0x63D, 0x53);
            break;
        case 14:
            Scene_SetupParty(4);
            step                   = &g_SceneEventState.mode;
            *step                  = SCENE_EVENT_NONE;
            g_SceneEventState.step = 0;
            SYS_SetFlag(step + 0x63D, 0x52);
            SYS_SetFlag(step + 0x63D, 0x53);
            break;
        case 16:
            Scene_SetupParty(5);
            step                   = &g_SceneEventState.mode;
            *step                  = SCENE_EVENT_NONE;
            g_SceneEventState.step = 0;
            SYS_ClearFlag(step + 0x63D, 0x52);
            SYS_ClearFlag(step + 0x63D, 0x53);
            break;
    }
}

#include "area106_13.h"

MATCH void func_801F3B4C(void) {
    u8* step;

    switch (g_SceneEventStep) {
        case 0:
            func_801BE1B0(0);
            step             = &g_SceneEventMode;
            *step            = SCENE_EVENT_NONE;
            g_SceneEventStep = 0;
            SYS_SetFlag(step + 0x63D, 0x51);
            break;
        case 2:
            func_801BE1B0(1);
            step             = &g_SceneEventMode;
            *step            = SCENE_EVENT_NONE;
            g_SceneEventStep = 0;
            SYS_ClearFlag(step + 0x63D, 0x51);
            break;
        case 10:
            func_801BE1B0(2);
            step             = &g_SceneEventMode;
            *step            = SCENE_EVENT_NONE;
            g_SceneEventStep = 0;
            SYS_SetFlag(step + 0x63D, 0x52);
            SYS_ClearFlag(step + 0x63D, 0x53);
            break;
        case 12:
            func_801BE1B0(3);
            step             = &g_SceneEventMode;
            *step            = SCENE_EVENT_NONE;
            g_SceneEventStep = 0;
            SYS_ClearFlag(step + 0x63D, 0x52);
            SYS_SetFlag(step + 0x63D, 0x53);
            break;
        case 14:
            func_801BE1B0(4);
            step             = &g_SceneEventMode;
            *step            = SCENE_EVENT_NONE;
            g_SceneEventStep = 0;
            SYS_SetFlag(step + 0x63D, 0x52);
            SYS_SetFlag(step + 0x63D, 0x53);
            break;
        case 16:
            func_801BE1B0(5);
            step             = &g_SceneEventMode;
            *step            = SCENE_EVENT_NONE;
            g_SceneEventStep = 0;
            SYS_ClearFlag(step + 0x63D, 0x52);
            SYS_ClearFlag(step + 0x63D, 0x53);
            break;
    }
}

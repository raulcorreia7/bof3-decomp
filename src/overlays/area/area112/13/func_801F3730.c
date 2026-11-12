#include "area112_13.h"

MATCH void func_801F3730(void) {
    g_MessageRequest = g_MessageChoice + 3;
    SYS_SetFlag(g_SceneEventFlags, 0x33);
    switch (g_MessageChoice) {
        case 0:
        default:
            SYS_ClearFlag(g_SceneEventFlags, 0x34);
            SYS_ClearFlag(g_SceneEventFlags, 0x35);
            break;
        case 1:
            SYS_ClearFlag(g_SceneEventFlags, 0x34);
            SYS_SetFlag(g_SceneEventFlags, 0x35);
            break;
        case 2:
            SYS_SetFlag(g_SceneEventFlags, 0x34);
            SYS_ClearFlag(g_SceneEventFlags, 0x35);
            break;
        case 3:
            SYS_SetFlag(g_SceneEventFlags, 0x34);
            SYS_SetFlag(g_SceneEventFlags, 0x35);
            break;
        case 4:
            g_MessageRequest = MESSAGE_NONE;
            break;
    }
    if (SYS_TestFlag(D_80144EF0, 0x10) == 0) {
        g_MessageRequest = 2;
        /* FAKE: retail reaches g_SceneEventFlags as D_80144EF0 + 0x38, so the offset stays. */
        SYS_ClearFlag(D_80144EF0 + 0x38, 0x33);
    }
}

#include "area100_13.h"

MATCH void func_801F37AC(void) {
    s8 choice;

    choice             = g_UIMessageChoice;
    g_UIMessageRequest = D_801F4F5C[choice];
    switch (choice) {
        case 0:
        default:
            SYS_SetFlag(g_SceneEventFlags, 0x93);
            SYS_ClearFlag(g_SceneEventFlags, 0x94);
            SYS_SetFlag(g_SceneEventFlags, 0x33);
            break;
        case 1:
            SYS_ClearFlag(g_SceneEventFlags, 0x93);
            SYS_SetFlag(g_SceneEventFlags, 0x94);
            SYS_SetFlag(g_SceneEventFlags, 0x33);
            break;
        case 2:
            SYS_ClearFlag(g_SceneEventFlags, 0x93);
            SYS_ClearFlag(g_SceneEventFlags, 0x94);
            SYS_SetFlag(g_SceneEventFlags, 0x33);
            break;
        case 3:
            if (Item_VitalHas(VITAL_ITEM_ID_CARD)) {
                SYS_SetFlag(g_SceneEventFlags, 0x93);
                SYS_SetFlag(g_SceneEventFlags, 0x94);
                SYS_SetFlag(g_SceneEventFlags, 0x33);
            } else {
                g_UIMessageRequest = MSG_AREA100_PORTAL_CODE_FAILED;
                SYS_ClearFlag(g_SceneEventFlags, 0x33);
            }
            break;
        case 4:
            break;
    }
}

#include "area040_13.h"

MATCH void func_801F2CB4(void) {
    u8* flags;

    MESSAGE_REQUEST_CLEAR();
    if (MENU_SELECTION_ARMED()) {
        D_80146875 = 0x1E;
    } else {
        D_80146875 = 0x1C;
    }
    SYS_SetFlag(g_SceneFlags, 5);
    flags = &g_SceneState.flags_01;
    g_GameFlags &= 0xFF77;
    *flags &= 0xBF;
}

#include "area193_13.h"

MATCH void func_801F31C0(void) {
    if (SYS_TestFlag(g_SceneEventFlags, 138)) {
        g_SceneEventMode = 0x39;
        g_AreaDrawFlags  = 0;
        g_SceneEventStep = 0x14;
    } else {
        g_GameRequestKind = 1;
    }
}

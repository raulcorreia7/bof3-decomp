#include "area141_13.h"

MATCH void func_801F3A38(void) {
    SYS_SetFlag(g_SceneEventFlags, 125);
    if (g_MessageChoice == 0) {
        Game_SetScriptActive();
        func_801C601C(3);
        func_801F4300(D_801F4DBC, 0);
        g_SceneEventMode = 0x34;
        g_SceneEventStep = 0x32;
        g_MessageRequest = 5;
    } else {
        g_MessageRequest = 6;
    }
}

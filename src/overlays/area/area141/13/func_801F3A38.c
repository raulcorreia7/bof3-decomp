#include "area141_13.h"

MATCH void func_801F3A38(void) {
    SYS_SetFlag(g_SceneEventFlags, 0x7D);
    if (D_801490C7 == 0) {
        Game_SetScriptActive();
        func_801C601C(3);
        func_801F4300(D_801F4DBC, 0);
        D_801448EB       = 0x34;
        D_801448EC       = 0x32;
        g_MessageRequest = 5;
    } else {
        g_MessageRequest = 6;
    }
}

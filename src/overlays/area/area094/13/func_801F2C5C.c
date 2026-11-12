#include "area094_13.h"

MATCH void func_801F2C5C(void) {
    g_MessageRequest = D_801F5354[g_MessageChoice];
    if (g_MessageChoice != 0) {
        if (g_MessageChoice == 1) {
            SYS_SetFlag(g_SceneFlags, 21);
        }
    }
}

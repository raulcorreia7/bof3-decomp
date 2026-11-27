#include "area094_13.h"

MATCH void func_801F2C5C(void) {
    g_UIMessageRequest = D_801F5354[g_UIMessageChoice];
    if (g_UIMessageChoice != 0) {
        if (g_UIMessageChoice == 1) {
            SYS_SetFlag(g_SceneFlags, 21);
        }
    }
}

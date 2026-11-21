#include "area094_13.h"

MATCH void func_801F2C5C(void) {
    g_UiMessageRequest = D_801F5354[g_UiMessageChoice];
    if (g_UiMessageChoice != 0) {
        if (g_UiMessageChoice == 1) {
            SYS_SetFlag(g_SceneFlags, 21);
        }
    }
}

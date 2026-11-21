#include "area140_13.h"

MATCH void func_801F3D4C(void) {
    s32 message;

    if (g_UiMessageChoice == 0) {
        message = 4;
    } else {
        if (g_UiMessageChoice == 1) {
            Scene_StartEvent(0x29, 0);
        }
        message = 0xFFFF;
    }
    g_UiMessageRequest = message;
}

#include "area140_13.h"

MATCH void func_801F3D4C(void) {
    s32 message;

    if (g_UIMessageChoice == 0) {
        message = 4;
    } else {
        if (g_UIMessageChoice == 1) {
            Scene_StartEvent(0x29, 0);
        }
        message = 0xFFFF;
    }
    g_UIMessageRequest = message;
}

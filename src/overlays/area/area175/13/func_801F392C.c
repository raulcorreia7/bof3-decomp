#include "area175_13.h"

MATCH void func_801F392C(void) {
    if (g_MessageChoice == 1) {
        g_MessageRequest = 0x5F;
        g_SceneEventStep = 1;
    } else {
        MESSAGE_REQUEST_CLEAR();
    }
}

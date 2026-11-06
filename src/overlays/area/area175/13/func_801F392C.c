#include "area175_13.h"

MATCH void func_801F392C(void) {
    if (D_801490C7 == 1) {
        g_MessageRequest            = 0x5F;
        g_SaveData.scene_event.step = 1;
    } else {
        MESSAGE_REQUEST_CLEAR();
    }
}

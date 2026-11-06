#include "area168_13.h"

MATCH s32 func_801F48B4(void) {
    u16 message;

    if (D_801490C7 == 0) {
        if (Item_VitalHas(0xD) != 0) {
            g_MessageRequest = 6;
            g_AreaSceneMode |= 2;
            return;
        }
        message = 7;
    } else {
        message = 0xFFFF;
    }
    g_MessageRequest = message;
}

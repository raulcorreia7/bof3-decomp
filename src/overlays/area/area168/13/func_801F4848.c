#include "area168_13.h"

MATCH void func_801F4848(void) {
    u16 message;

    if (g_MessageChoice == 0) {
        if (Item_VitalHas(0xC) != 0) {
            g_MessageRequest = 6;
            g_AreaSceneMode |= 1;
            return;
        }
        message = 7;
    } else {
        message = 0xFFFF;
    }
    g_MessageRequest = message;
}

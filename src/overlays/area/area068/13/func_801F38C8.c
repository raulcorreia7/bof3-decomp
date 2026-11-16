#include "area068_13.h"

MATCH void func_801F38C8(void) {
    u16 message;

    if (g_MessageChoice == 0) {
        if ((Item_CountHeld(1) & BYTE_MASK) >= 15U) {
            g_MessageRequest = AREA068_MSG_MASTER_ACCEPTS;
            return;
        }
        message = AREA068_MSG_WEAPONS_NEEDED;
    } else {
        message = AREA068_MSG_MASTER_FAREWELL;
    }
    g_MessageRequest = message;
    g_MenuMasterStep = 6;
}

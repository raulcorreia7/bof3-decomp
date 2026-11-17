#include "area068_13.h"

MATCH void func_801F38C8(void) {
    u16 message;

    if (g_MessageChoice == 0) {
        if ((Item_CountHeld(1) & BYTE_MASK) >= 15U) {
            g_MessageRequest = MSG_AREA068_MASTER_ACCEPT_APPRENTICE;
            return;
        }
        message = MSG_AREA068_MASTER_NEEDS_ITEM;
    } else {
        message = MSG_AREA068_MASTER_FAREWELL;
    }
    g_MessageRequest = message;
    g_MenuMasterStep = 6;
}

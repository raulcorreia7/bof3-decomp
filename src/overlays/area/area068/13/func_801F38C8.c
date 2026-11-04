#include "area068_13.h"

MATCH void func_801F38C8(void) {
    u16 message;

    if (D_801490C7 == 0) {
        if ((Party_CountInventory(1) & BYTE_MASK) >= 15U) {
            g_MessageRequest = 0x82;
            return;
        }
        message = 0x83;
    } else {
        message = 0x84;
    }
    g_MessageRequest = message;
    g_MasterStep     = 6;
}

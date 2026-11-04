#include "area041_13.h"

MATCH void func_801F3BCC(void) {
    u16 value;

    if (D_801490C7 == 0) {
        if ((Party_CountItem(0, 0x49, 0) & 0xFFFF) && (Party_CountItem(0, 0x3F, 0) & 0xFFFF) &&
            (Party_CountItem(0, 0x27, 0) & 0xFFFF) && (Party_CountItem(0, 0x1D, 0) & 0xFFFF)) {
            Party_RemoveItem(0, 0x49U, 1, 0);
            Party_RemoveItem(0, 0x3FU, 1, 0);
            Party_RemoveItem(0, 0x27U, 1, 0);
            Party_RemoveItem(0, 0x1DU, 1, 0);
            g_MessageRequest = 0x62;
            return;
        }
        value = 0x63;
    } else {
        value = 0x64;
    }
    g_MessageRequest = value;
    g_MasterStep     = 6;
}

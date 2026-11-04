#include "area041_13.h"

MATCH void func_801F3BCC(void) {
    u16 var_v0;

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
        var_v0 = 0x63;
        goto block_8;
    }
    var_v0 = 0x64;
block_8:
    g_MessageRequest = var_v0;
    g_MasterStep     = 6;
}

#include "area091_13.h"

MATCH void func_801F2C04(void) {
    if (MENU_SELECTION_IDLE()) {
        if (Party_CountItem(0, 0x59, 0) != 0) {
            Party_RemoveItem(0, 0x59, 1, 0);
            g_MessageRequest = 5;
            return;
        }
        g_MessageRequest = 6;
    } else {
        g_MessageRequest = 7;
    }
    g_MasterStep = 6;
}

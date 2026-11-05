#include "area055_13.h"

MATCH void func_801F2C04(void) {
    if (MENU_SELECTION_IDLE()) {
        if ((Item_Count(ITEM_CAT_ITEM, 8, 0) & HALF_MASK) != 0) {
            Item_Remove(ITEM_CAT_ITEM, 8, 1, 0);
            g_MessageRequest = 0x22;
            return;
        }
        g_MessageRequest = 0x23;
    } else {
        g_MessageRequest = 0x24;
    }
    g_MasterStep = 6;
}

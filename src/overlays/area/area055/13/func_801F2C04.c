#include "area055_13.h"

MATCH s32 func_801F2C04(void) {
    if (MENU_SELECTION_IDLE()) {
        if ((Item_Count(ITEM_CAT_ITEM, ITEM_WISDOM_FRUIT, 0) & 0xFFFF) != 0) {
            Item_Remove(ITEM_CAT_ITEM, ITEM_WISDOM_FRUIT, 1, 0);
            g_MessageRequest = 0x22;
            return;
        }
        g_MessageRequest = 0x23;
    } else {
        g_MessageRequest = 0x24;
    }
    g_MasterStep = 6;
}

#include "area091_13.h"

MATCH void func_801F2C04(void) {
    if (MENU_SELECTION_IDLE()) {
        if (Item_Count(ITEM_CAT_ITEM, ITEM_FLOWER_JEWEL, 0) != 0) {
            Item_Remove(ITEM_CAT_ITEM, ITEM_FLOWER_JEWEL, 1, 0);
            g_MessageRequest = 5;
            return;
        }
        g_MessageRequest = 6;
    } else {
        g_MessageRequest = 7;
    }
    g_MasterStep = 6;
}

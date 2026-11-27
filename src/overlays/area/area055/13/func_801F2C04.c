#include "area055_13.h"

MATCH s32 func_801F2C04(void) {
    if (MENU_SELECTION_IDLE()) {
        if ((Item_Count(ITEM_CATEGORY_ITEM, ITEM_WISDOM_FRUIT, 0) & HALF_MASK) != 0) {
            Item_Remove(ITEM_CATEGORY_ITEM, ITEM_WISDOM_FRUIT, 1, 0);
            g_UIMessageRequest = MSG_AREA055_MASTER_ITEM_RECEIVED;
            return;
        }
        g_UIMessageRequest = MSG_AREA055_MASTER_NO_ITEM;
    } else {
        g_UIMessageRequest = MSG_AREA055_MASTER_FAREWELL;
    }
    g_MenuMasterStep = 6;
}

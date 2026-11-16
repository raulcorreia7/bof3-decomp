#include "area055_13.h"

MATCH s32 func_801F2C04(void) {
    if (MENU_SELECTION_IDLE()) {
        if ((Item_Count(ITEM_CAT_ITEM, ITEM_WISDOM_FRUIT, 0) & HALF_MASK) != 0) {
            Item_Remove(ITEM_CAT_ITEM, ITEM_WISDOM_FRUIT, 1, 0);
            g_MessageRequest = AREA055_MSG_WISDOM_FRUIT_GIVEN;
            return;
        }
        g_MessageRequest = AREA055_MSG_WISDOM_FRUIT_MISSING;
    } else {
        g_MessageRequest = AREA055_MSG_MASTER_FAREWELL;
    }
    g_MenuMasterStep = 6;
}

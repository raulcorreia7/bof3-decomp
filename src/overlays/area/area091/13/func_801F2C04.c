#include "area091_13.h"

MATCH s32 func_801F2C04(void) {
    if (MENU_SELECTION_IDLE()) {
        if (Item_Count(ITEM_CATEGORY_ITEM, ITEM_FLOWER_JEWEL, 0) != 0) {
            Item_Remove(ITEM_CATEGORY_ITEM, ITEM_FLOWER_JEWEL, 1, 0);
            g_UIMessageRequest = MSG_AREA091_MASTER_ACCEPT_APPRENTICE;
            return;
        }
        g_UIMessageRequest = MSG_AREA091_MASTER_NO_ITEM;
    } else {
        g_UIMessageRequest = MSG_AREA091_MASTER_FAREWELL;
    }
    g_MenuMasterStep = 6;
}

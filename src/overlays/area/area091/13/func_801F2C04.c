#include "area091_13.h"

MATCH s32 func_801F2C04(void) {
    if (MENU_SELECTION_IDLE()) {
        if (Item_Count(ITEM_CAT_ITEM, ITEM_FLOWER_JEWEL, 0) != 0) {
            Item_Remove(ITEM_CAT_ITEM, ITEM_FLOWER_JEWEL, 1, 0);
            g_MessageRequest = AREA091_MSG_AGILITY_TERMS;
            return;
        }
        g_MessageRequest = AREA091_MSG_ITEM_MISSING;
    } else {
        g_MessageRequest = AREA091_MSG_MASTER_FAREWELL;
    }
    g_MenuMasterStep = 6;
}

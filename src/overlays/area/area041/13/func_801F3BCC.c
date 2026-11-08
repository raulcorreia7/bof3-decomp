#include "area041_13.h"

MATCH void func_801F3BCC(void) {
    u16 value;

    if (g_MessageChoice == 0) {
        if ((Item_Count(ITEM_CAT_ITEM, ITEM_ANGLER, 0) & HALF_MASK) &&
            (Item_Count(ITEM_CAT_ITEM, ITEM_MARTIAN_SQUID, 0) & HALF_MASK) &&
            (Item_Count(ITEM_CAT_ITEM, ITEM_BEEF_JERKY, 0) & HALF_MASK) &&
            (Item_Count(ITEM_CAT_ITEM, ITEM_SWALLOW_EYE, 0) & HALF_MASK)) {
            Item_Remove(ITEM_CAT_ITEM, ITEM_ANGLER, 1, 0);
            Item_Remove(ITEM_CAT_ITEM, ITEM_MARTIAN_SQUID, 1, 0);
            Item_Remove(ITEM_CAT_ITEM, ITEM_BEEF_JERKY, 1, 0);
            Item_Remove(ITEM_CAT_ITEM, ITEM_SWALLOW_EYE, 1, 0);
            g_MessageRequest = 0x62;
            return;
        }
        value = 0x63;
    } else {
        value = 0x64;
    }
    g_MessageRequest = value;
    g_MenuMasterStep = 6;
}

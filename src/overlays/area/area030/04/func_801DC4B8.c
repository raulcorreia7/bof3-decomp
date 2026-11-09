#include "area030_04.h"

/* Submits mask `g_FishingLure` to `Item_Remove` as mode 3. */
MATCH void func_801DC4B8(void) {
    u8* flags;

    flags = &g_FishingLure;
    if (Item_Remove(ITEM_CAT_ACCESSORY, *flags, 1, 0) == 0) {
        *flags           = 0;
        g_FishingLureQty = 0;
    }
    func_801DDDBC();
}

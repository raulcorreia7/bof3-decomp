#include "area030_04.h"

/* Submits the equipped lure to `Item_Remove` as mode 3; when it
 * reports failure, clears the lure and its count. Always refreshes the
 * state through `func_801DDDBC`. */
MATCH void func_801DC4B8(void) {
    u8* flags;

    flags = &g_FishingEquipment.lure_id;
    if (Item_Remove(ITEM_CATEGORY_ACCESSORY, *flags, 1, 0) == 0) {
        *flags                        = 0;
        g_FishingEquipment.lure_count = 0;
    }
    func_801DDDBC();
}

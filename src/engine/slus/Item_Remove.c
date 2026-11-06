#include "engine/slus/slus.h"

/* subtracts amount from the slot of item in the category rows; clears the slot when it reaches zero.
 * Returns 0 when the item is absent or the stack is short. */
MATCH u8 Item_Remove(s32 category, u8 item, s32 amount, s32 unused) {
    u8* ids;
    u8* qtys;
    u32 index;
    u8  qty;
    if (item == 0)
        return false;
    if ((amount & 0xFF) == 0)
        return false;
    ids   = D_801C893C[category & 0xFF];
    qtys  = D_801C8950[category & 0xFF];
    index = 0;
    while ((index & 0xFF) < INV_SLOTS_PER_CATEGORY) {
        if (*ids == item) {
            qty = *qtys;
            if (qty >= (u32)(amount & 0xFF)) {
                *qtys -= amount;
                if (*qtys == 0)
                    *ids = 0;
                return true;
            }
            return false;
        }
        ids++;
        qtys++;
        index++;
    }
    return false;
}

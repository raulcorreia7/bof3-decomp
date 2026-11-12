#include "engine/slus/slus.h"

/* subtracts count from the slot of item_id in the category rows; clears the slot when it reaches zero.
 * Returns 0 when the item_id is absent or the stack is short. */
MATCH u8 Item_Remove(s32 category, u8 item_id, s32 count, s32 unused) {
    u8* ids;
    u8* qtys;
    u32 index;
    u8  qty;
    if (item_id == 0)
        return false;
    if ((count & BYTE_MASK) == 0)
        return false;
    ids   = D_801C893C[category & BYTE_MASK];
    qtys  = D_801C8950[category & BYTE_MASK];
    index = 0;
    while ((index & BYTE_MASK) < INV_SLOTS_PER_CATEGORY) {
        if (*ids == item_id) {
            qty = *qtys;
            if (qty >= (u32)(count & BYTE_MASK)) {
                *qtys -= count;
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

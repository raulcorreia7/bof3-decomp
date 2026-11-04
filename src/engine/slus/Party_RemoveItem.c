#include "engine/slus/slus.h"

/* subtracts amount from the slot of item in the category rows; clears the slot when it reaches zero.
 * Returns 0 when the item is absent or the stack is short. */
MATCH u8 Party_RemoveItem(s32 category, u8 item, s32 amount, s32 unused) {
    u8* ids;
    u8* qtys;
    u32 index;
    u8  qty;
    if (item == 0)
        return false;
    if ((amount & BYTE_MASK) == 0)
        return false;
    ids   = D_801C893C[category & BYTE_MASK];
    qtys  = D_801C8950[category & BYTE_MASK];
    index = 0;
    while ((u32)(index & BYTE_MASK) < INV_SLOTS_PER_CATEGORY) {
        if (*ids == item) {
            qty = *qtys;
            if (qty >= (u32)(amount & BYTE_MASK)) {
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

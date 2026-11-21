#include "engine/slus/slus.h"

/* counts the non-zero bytes of the selected inventory record slot.
 */
MATCH u8 Item_CountHeld(u32 category) {
    u8* p;
    u8  count;
    u8  index;
    u8  limit;

    count = 0;
    p     = D_801C893C[category & BYTE_MASK];
    if ((category & BYTE_MASK) < 4u) {
        limit = 128;
    } else {
        limit = 32;
    }
    index = 0;
    if (limit != 0) {
        do {
            if (*p != 0) {
                count += 1;
            }
            index += 1;
            p += 1;
        } while (index < limit);
    }
    return count;
}

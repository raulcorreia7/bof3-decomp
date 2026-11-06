#include "engine/slus/slus.h"

/* counts the non-zero bytes of the selected inventory record slot.
 */
MATCH s32 Item_CountHeld(u32 category) {
    u8* p;
    u8  count;
    u8  index;
    u8  limit;

    count = 0;
    p     = D_801C893C[category & 0xFF];
    if ((category & 0xFF) < 4u) {
        limit = 0x80;
    } else {
        limit = 0x20;
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

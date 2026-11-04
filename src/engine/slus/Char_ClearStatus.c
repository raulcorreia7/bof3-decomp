#include "engine/slus/slus.h"

/* clears mask bits in a record's status word, reading either the
 * field records (0x80144968, stride 0xA4) or their battle copies (0x80145F04,
 * stride 0x140); returns true when a bit was cleared.
 */
MATCH u32 Char_ClearStatus(u8 index, u16 mask, u8 mode) {
    Character* record;
    u16        status;
    Character* store;
    char       i;

    i = index & BYTE_MASK;
    if ((mode & BYTE_MASK) == 0) {
        record = &g_Characters[i];
    } else {
        record = (Character*)(D_80145F04 + i * 0x140);
    }
    status = record->status;
    store  = record;
    if ((status & mask) != 0) {
        store->status = status & ~mask;
        return true;
    }
    return false;
}

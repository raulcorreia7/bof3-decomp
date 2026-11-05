#include "game_00.h"

/* Counts record id bytes matching target, fields selected by mode. */
MATCH s32 func_801C38F4(s32 record_index, s32 field_mode, s32 wanted_id) {
    Character* record;
    s32        mode;
    s32        target;
    s32        count;

    mode   = field_mode & BYTE_MASK;
    count  = record_index & BYTE_MASK;
    record = &g_Characters[g_CharSlot[count]];
    count  = 0;
    if (mode == 1) {
        goto mode1; /* mode 1 compares the record's 0x0E byte */
    }
    if (mode < 2) {
        goto done; /* mode 0 has no field to compare */
    }
    if (mode == 2) {
        goto mode2; /* mode 2 compares the record's 0x0F..0x11 bytes */
    }
    if (mode == 3) {
        goto mode3; /* mode 3 compares the record's 0x12..0x13 bytes */
    }
    goto done; /* an unknown mode counts nothing */
mode1:
    if (record->equipment.weapon == (wanted_id & BYTE_MASK)) {
        count = 1;
    }
    goto done; /* the mode-1 compare is done */
mode2:
    target = wanted_id & BYTE_MASK;
    if (record->equipment.shield == target) {
        count = 1;
    }
    if (record->equipment.helmet == target) {
        count += 1;
    }
    if (record->equipment.armor == target) {
        count += 1;
    }
    goto done; /* the mode-2 compares are done */
mode3:
    target = wanted_id & BYTE_MASK;
    if (record->equipment.accessories[0] == target) {
        count = 1;
    }
    if (record->equipment.accessories[1] == target) {
        count += 1;
    }
done:
    return count & BYTE_MASK;
}

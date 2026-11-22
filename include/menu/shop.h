#ifndef MENU_SHOP_H
#define MENU_SHOP_H

#include "types.h"

/* One save slot row: 0x1C bytes. The copy paths move it as seven words; the
 * drawers read the byte fields. Byte 0x15 holds the source-list index the row
 * was copied from, or 0xFF when the row is empty. */
typedef union SaveSlotRow {
    struct {
        u8 unk_00[0x15];
        u8 card_index; /* 0x15 - source-list index, 0xFF when empty */
        u8 unk_16[6];
    } bytes;

    s32 words[7];
} SaveSlotRow;

STATIC_ASSERT(SaveSlotRow_bytes_card_index, DECOMP_OFFSETOF(SaveSlotRow, bytes.card_index) == 0x15);
STATIC_ASSERT(SaveSlotRow_bytes_size, sizeof(((SaveSlotRow*)0)->bytes) == 0x1C);
ASSERT_SIZE(SaveSlotRow, 0x1C);

#endif

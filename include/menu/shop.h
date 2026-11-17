#ifndef MENU_SHOP_H
#define MENU_SHOP_H

#include "types.h"

/* One shop row: 0x1C bytes. Byte 0x15 holds the source-list index the row was
 * copied from, or 0xFF when the row is empty. */
typedef struct SaveSlotRow {
    u8 unk_00[0x15];
    u8 card_index; /* 0x15 - source-list index, 0xFF when empty */
    u8 unk_16[6];
} SaveSlotRow;

ASSERT_OFFSET(SaveSlotRow, card_index, 0x15);
ASSERT_SIZE(SaveSlotRow, 0x1C);

/* The same row as seven words: retail copies a source record into a row word-wise. */
typedef struct SaveSlotRowCopy {
    s32 unk_00;
    s32 unk_04;
    s32 unk_08;
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
    s32 unk_18;
} SaveSlotRowCopy;

ASSERT_SIZE(SaveSlotRowCopy, 0x1C);

#endif

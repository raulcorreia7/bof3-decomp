#ifndef MENU_SHOP_H
#define MENU_SHOP_H

#include "types.h"

/* One shop row: 0x1C bytes. Byte 0x15 holds the source-list index the row was
 * copied from, or 0xFF when the row is empty. */
typedef struct MenuListRow {
    u8 unk_00[0x15];
    u8 source_index; /* 0x15 - source-list index, 0xFF when empty */
    u8 unk_16[6];
} MenuListRow;

ASSERT_SIZE(MenuListRow, 0x1C);
ASSERT_OFFSET(MenuListRow, source_index, 0x15);

/* The same row as seven words: retail copies a source record into a row word-wise. */
typedef struct MenuListRowWords {
    s32 unk_00;
    s32 unk_04;
    s32 unk_08;
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
    s32 unk_18;
} MenuListRowWords;

ASSERT_SIZE(MenuListRowWords, 0x1C);

#endif

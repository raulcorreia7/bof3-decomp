#ifndef MENU_SHOP_H
#define MENU_SHOP_H

#include "types.h"

/* One save slot's row: 0x1C bytes. Byte 0x15 holds the memory-card directory
 * entry the row was copied from, or 0xFF when the row is empty. */
typedef struct SaveSlotRow {
    u8 name[5];       /* 0x00 - the save name */
    u8 party_icons[3]; /* 0x05 - the party portrait ids */
    u8 level;          /* 0x08 */
    u8 unk_09[3];     /* 0x09 */
    u8 play_hours;    /* 0x0C */
    u8 play_minutes;  /* 0x0D */
    u8 unk_0E[6];     /* 0x0E - the experience word at 0x10 is read through SaveSlotRowCopy */
    u8 has_data;      /* 0x14 - nonzero when the slot holds a save */
    u8 card_index;    /* 0x15 - the card-directory entry, 0xFF when empty */
    u8 unk_16[6];     /* 0x16 */
} SaveSlotRow;

ASSERT_OFFSET(SaveSlotRow, card_index, 0x15);
ASSERT_SIZE(SaveSlotRow, 0x1C);

/* The same row as seven words: retail copies a source record into a row
 * word-wise, and the drawer reads the experience word through it. */
typedef struct SaveSlotRowCopy {
    s32 unk_00;
    s32 unk_04;
    s32 unk_08;
    s32 unk_0C;
    s32 experience; /* 0x10 */
    s32 unk_14;
    s32 unk_18;
} SaveSlotRowCopy;

ASSERT_SIZE(SaveSlotRowCopy, 0x1C);

/* One memory-card directory entry: the save file's name and its size. */
typedef struct SaveFile {
    char name[20];
    s32  size;
} SaveFile;

ASSERT_SIZE(SaveFile, 0x18);
ASSERT_OFFSET(SaveFile, name, 0x00);
ASSERT_OFFSET(SaveFile, size, 0x14);

#endif

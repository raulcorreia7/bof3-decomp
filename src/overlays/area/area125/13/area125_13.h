#ifndef OVERLAY_WORLD03_AREA125_13_H
#define OVERLAY_WORLD03_AREA125_13_H

/* The world03/area125/13 overlay: one file per split function
 * and its data. Only this image includes the file. */

#include "overlays/area/world03.h"
#include "work/area_spad.h"

/* The work-window byte offset and row stride this overlay scans. */
#define SCRATCH_ROW_OFFSET   0x00
#define SCRATCH_ROW_STRIDE   0x28

/* The row count this overlay clears. */
#define SCRATCH_COLUMN_COUNT 16

typedef struct AreaSprite {
    u8  unk_00[3];
    u8  flags_03;  /* the shade of the sprite */
    u16 half_size; /* the projected half-size */
    u8  unk_06[2];
    s32 origin_x; /* the camera x */
    s32 origin_y; /* the camera y */
    s32 unk_10;
    s32 unk_14;
    s32 unk_18;
    s32 unk_1C;
    s32 unk_20;
    s32 unk_24;
} AreaSprite;

extern u8 D_801F364C[];
extern u8 D_801F364E[];
extern u8 D_801F368C[];
extern u8 D_801F368E[];

/* func_801F3384 */
void Area_ClearWorkColumn(void);
s32  func_801F33B0(void);
void func_801F3504(void);
void func_801F31B0(s32 arg0);

#endif

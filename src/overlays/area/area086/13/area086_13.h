#ifndef OVERLAY_WORLD02_AREA086_13_H
#define OVERLAY_WORLD02_AREA086_13_H

/* The world02/area086/13 overlay: one file per split function
 * and its data. Only this image includes the file. */

#include "overlays/area/worlds/world02.h"

extern Callback D_801F3658[];

/* A span of map cells: the first column and row, then the column and row it stops before. */
typedef struct AreaCellSpan {
    u8 x0;
    u8 y0;
    u8 x_end;
    u8 y_end;
} AreaCellSpan;

/* The cell span of each gate position, indexed by the task's cell x. */
extern AreaCellSpan D_801F364C[];

void       func_801F2DE8(void);
void       func_801F3070(void);
extern u8  D_801F3664[];
extern u16 D_801F3668[];

/* The ground height step of each cell, read by func_801F2D28 in signed rows. */
extern s8 D_801F3670[];

/* The three cell triggers: the cell pair, the facing that arms one and the flag it turns on. */
extern u8 D_801F3CEC[];
extern u8 D_801F3CED[];
extern u8 D_801F3CEE[];
extern u8 D_801F3CEF[];
/* The cell rectangle each trigger scans. */
extern u8 D_801F3CF8[];
extern u8 D_801F3CF9[];
extern u8 D_801F3CFA[];
extern u8 D_801F3CFB[];

/* One quad of the overlay's part table: the packed cell word (bytes: depth row, shape, cell y,
 * cell x) and the tile word Area_ApplyTileToQuad reads. */
typedef struct AreaQuadPart {
    union {
        u32 packed;
        u8  bytes[4];
    } cell;

    u32 tile;
} AreaQuadPart;

/* The two cell depths of each depth row: [0] while pos.z is -0x200, else [1]. */
extern s8           D_801F3674[][2];
/* The first and end part of each part range func_801F3070 draws. */
extern u8           D_801F367C[][2];
/* The four corner offsets (x, y, z) of each quad shape, in 128-unit steps. */
extern s8           D_801F3684[][4][3];
extern AreaQuadPart D_801F36C0[];

s8 Area_FindMemberAt(s32 x, s32 y);

#endif

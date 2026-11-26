#ifndef OVERLAY_WORLD02_AREA112_13_H
#define OVERLAY_WORLD02_AREA112_13_H

/* The world02/area112/13 overlay: one file per split function
 * and its data. Only this image includes the file. */

#include "overlays/area/worlds/world02.h"

/* The scenario flag byte the answer path tests. */
extern u8 D_80144EF0[];

/* The battle record rows whose first byte is the slot tag. */
extern u8 D_801F41F8[];

/* The two cell depths of each depth row: [1] while the task step is 2, else [0]. */
extern s8                  D_801F4240[][2];
/* The first and end part of each part range func_801F3274 draws. */
extern u8                  D_801F4250[][2];
/* The four corner offsets (x, y, z) of each quad shape, in 128-unit steps. */
extern s8                  D_801F4258[][4][3];
extern AreaQuadPart        D_801F4294[];
/* D_801F48FC */
extern PartyMemberMessages g_PartyMemberMessages[1];
extern u8                  D_801F493C[];

void func_801F2EA8(void);
void func_801F3274(void);
void Area_DrawLightPillar(s32* pos);

/* The map bundle as bytes, and its width byte read at the constant address. */
#define AREA112_MAP_BYTES ((u8*)MAP_BUNDLE_BASE)
#define AREA112_MAP_WIDTH (*AREA112_MAP_BYTES)

/* The scene flag id of each cell the step handles, by cell column. */
extern u8  D_801F420C[];
/* The ground height of each cell, by cell column. */
extern u16 D_801F4210[];

/* The gate span of each cell column: first and end cell, the ends exclusive. */
extern AreaCellSpan D_801F4218[];
/* The gate shade bytes, eleven a flag row, one a span cell. */
extern u8           D_801F4228[][11];

/* An answer cell: the cell x and y, the flag mask and the flag the answer toggles. */
typedef struct AnswerCell {
    /* 0x0 */ u8 x;
    /* 0x1 */ u8 y;
    /* 0x2 */ u8 flag_mask; /* low four bits clear a direction flag, high four set it */
    /* 0x3 */ u8 flag_id;
} AnswerCell;

ASSERT_SIZE(AnswerCell, 4);

/* The four answer cells of the area. */
extern AnswerCell D_801F4908[4];
/* The first four answer flags, cleared by the low four mask bits and set by the high four. */
extern u8         D_801F4928[4];

/* A cell and the reach around it on each axis. */
typedef struct CellZone {
    /* 0x00 */ u8 x;
    /* 0x01 */ u8 y;
    /* 0x02 */ u8 reach_x;
    /* 0x03 */ u8 reach_y;
} CellZone;

ASSERT_SIZE(CellZone, 0x04);
/* The four zones func_801F3CF0 tests the party against. */
extern CellZone D_801F492C[4];

/* The height-table byte offset as the scalar retail reads: one lui per access.
 * Same cell as AreaMapBundle.height_offset. */
extern u16 g_AreaMapHeightOffset;
s8         Area_FindMemberAt(s32 x, s32 y);
bool       func_801F3CF0(void);

#endif

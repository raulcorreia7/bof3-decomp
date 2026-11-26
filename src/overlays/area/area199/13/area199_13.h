#ifndef OVERLAY_WORLD04_AREA199_13_H
#define OVERLAY_WORLD04_AREA199_13_H

/* The world04/area199/13 overlay: one file per split function
 * and its data. Only this image includes the file. */

#include "overlays/area/worlds/world04.h"

/* The shade fan's triangle count: one triangle per 64-unit angle step. */
#define AREA_SHADE_FAN_SEGMENTS 64

/* The scratchpad work row the update passes read. */

/* The map-click frame word the scroll step subtracts from. */

/* The image's palette and cell tables. */
extern u8 D_801F44B4[];

/* One backdrop cell sprite: the screen rectangle, the texture page and the four texture cells. */
typedef struct Area199CellSprite {
    u16 x;
    u16 y;
    u16 w;
    u16 h;
    u8  page;
    u8  u;
    u8  v;
    u8  u_size;
    u8  v_size;
    u8  pad;
} Area199CellSprite;

ASSERT_SIZE(Area199CellSprite, 0xE);

/* The step handler bank. */
extern Callback          D_801F44B8[];
extern Area199CellSprite D_801F44D4[];
/* The trail part words and row offsets of the two members; their cells are in
 * g_Area199TrailCells. */
extern u8                D_801F4544[];
extern u8                D_801F4545[];
extern u8                D_801F4548[];
extern u8                D_801F54D0[];

/* A trail slot of one member: the cell and its tile flag. */
typedef struct Area199TrailCell {
    u8 x;
    u8 y;
    u8 flag;
} Area199TrailCell;

extern Area199TrailCell g_Area199TrailCells[32][2]; /* D_801F54D0 */
extern s8               D_801F54D2;
extern s8               D_801F54D5;

void func_801F2E14(void);
void func_801F2E80(s32 y_offset);
/* The image's step passes. */
void func_801F3398(void);
void func_801F400C(void);

void func_801F36DC(void);

#endif

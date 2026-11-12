#ifndef OVERLAY_WORLD03_AREA141_13_H
#define OVERLAY_WORLD03_AREA141_13_H

/* The world03/area141/13 overlay: one file per split function
 * and its data. Only this image includes the file. */

#include "overlays/area/world03.h"
#include "area/spad.h"

/* The scratchpad work pointer; the dispatch entry bytes select a handler. */

/* The fixed work record the dispatch compares the work pointer against. */
extern Actor D_80143F48;
extern u8    D_80144EF8[];

/* The state handler tables the dispatchers index. */
extern Callback D_801F47E8[];
extern u8       D_801F4D94;
extern u8       D_801F4DBC[];
extern Callback D_801F4DC4[];

void func_801F390C(void);
void func_801F3740(void);

extern Callback D_801F4DCC[];
extern u8       D_801F4DDC[];
extern u8       D_801F4E0C[];
extern u8       D_801F4E2C[];

void func_801A65A0(u8* script);
void Actor_BeginScript(s32 raw_selector, s32 raw_code);
void func_801F4300(u8* table, s32 arg);

extern u8 D_801F4DFC[];

/* The game-overlay state bytes the cancel path resets. */
extern u8 D_801F4E50[];

/* The cells that start the scene events of func_801F4158. */
extern SceneTrigger D_801F4DD4[];

/* A block of map cells: the first and last column and row, all included. The
 * upload step of func_801F2D2C reads one block per work x position. */
typedef struct CellBlock {
    u8 x0;
    u8 y0;
    u8 x1;
    u8 y1;
} CellBlock;

ASSERT_SIZE(CellBlock, 0x04);
ASSERT_OFFSET(CellBlock, y0, 0x01);
ASSERT_OFFSET(CellBlock, x1, 0x02);
ASSERT_OFFSET(CellBlock, y1, 0x03);

/* The part-word bits the upload step clears before the cell re-stages its rows. */
#define CELL_UPLOAD_MASK (~(0x1F << 19))

extern CellBlock D_801F47D4[];
/* The primitive rows one cell id selects, two per row. */
extern POLY_FT4  g_AreaCellPrims[][2];

#endif

#ifndef OVERLAY_WORLD03_AREA141_13_H
#define OVERLAY_WORLD03_AREA141_13_H

/* The world03/area141/13 overlay: one file per split function
 * and its data. Only this image includes the file. */

#include "overlays/area/worlds/world03.h"

/* The scratchpad work pointer; the dispatch entry bytes select a handler. */

/* The fixed work record the dispatch compares the work pointer against. */
extern Actor D_80143F48;

/* The state handler tables the dispatchers index. */
extern Callback D_801F47E8[];
/* The angular speed of the marker ring's wave, one per row parity. */
extern s8       D_801F47F4[];
extern u8       D_801F4D94;
/* The 5-byte cell-run rows at rows 2, 4 and 6 of the D_801F4D94 table; the
 * 0x7A, 0x7B and 0x7C flags retire them. */
extern u8       D_801F4D9E[];
extern u8       D_801F4DA8[];
extern u8       D_801F4DB2[];
extern u8       D_801F4DBC[];
extern Callback D_801F4DC4[];

void func_801F390C(void);
void func_801F3740(void);

extern Callback D_801F4DCC[];
extern u8       D_801F4DDC[];
extern u8       D_801F4E0C[];
extern u8       D_801F4E2C[];

/* func_801F4300 */
void Area_CellSetRun(u8* table, u8 arg);

/* The cells that start the scene events of func_801F4158. */
extern SceneTrigger D_801F4DD4[];
extern u8           D_801F4DFC[];

/* The game-overlay state bytes the cancel path resets. */
extern u8 D_801F4E50[];

/* The five-bit fade field of a cell entry: bit 19, filled up to CELL_FADE_MAX by the fade-in step. */
#define CELL_FADE_SHIFT  19
#define CELL_FADE_MAX    0x10
/* The part-word bits the upload steps clear before a cell re-stages its rows. */
#define CELL_UPLOAD_MASK (~(0x1F << CELL_FADE_SHIFT))

extern CellBlock D_801F47D4[];
/* The primitive rows one cell id selects, two per row. */

#endif

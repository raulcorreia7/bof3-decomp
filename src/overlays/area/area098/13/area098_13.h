#ifndef OVERLAY_WORLD02_AREA098_13_H
#define OVERLAY_WORLD02_AREA098_13_H

/* The world02/area098/13 overlay: one file per split function
 * and its data. Only this image includes the file. */

#include "overlays/area/world02.h"
#include "work/area_spad.h"

/* The work-window byte offset and row stride this overlay scans. */
#define SCRATCH_ROW_OFFSET    0x00
#define SCRATCH_ROW_STRIDE    0x1C

/* The work-window byte offset, row stride and row count this overlay clears. */
#define SCRATCH_COLUMN_OFFSET 0
#define SCRATCH_COLUMN_STRIDE 0x18
#define SCRATCH_COLUMN_COUNT  8

#include "shared/WorldSpin.h"

#define AREA_SPIN_PRIM_ORDER 2

#define AREA_SPIN_RADIUS     16
#define AREA_SPIN_PITCH      (RANDOM_MASK(0x7FF) - 0x400)
#define AREA_SPIN_SCALE_MASK 0x2
#define AREA_SPIN_SCALE_BASE 3
#define AREA_SPIN_FADE       0x20

extern Callback D_801F5F68[];
extern Callback D_801F5F7C[];
extern Callback D_801F5F88[];
extern Callback D_801F5FAC[];
extern u8       D_801F6510;
extern u8       D_801F6514;

void        Area_ProjectPoint(s32* pos, long* screen_xy);
/* func_801F526C */
extern void Area_ClaimSpawnSlot(void);
/* func_801F5308 */
extern s32  Area_StepSpawnSlots(void);
extern void func_801F53BC(AreaSpawnSlot* slot);

#define AREA_SPAWN_SLOT_DRAW func_801F53BC
extern void func_801F5940(void);
void        func_801F4D44(void);
void        func_801F5050(u8 level);
void        Area_SetCellCode(s16 column, s16 row, u8 code);

extern u8 D_80146865;

extern u8 D_8014554C[];

#endif

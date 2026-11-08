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

extern s32      D_80145EC4[];
extern Callback D_801F5F68[];
extern Callback D_801F5F7C[];
extern Callback D_801F5F88[];
extern Callback D_801F5FAC[];
extern void (*D_801F5FBC[])(void* slot);
extern u8 D_801F6510;
extern u8 D_801F6514;

/* The per-image spawn step Area_AdvanceSpawnTimer runs between the slot claim and the slot pass. */
#define AREA_SPAWN_TICK             func_801F5940

#define AREA_SPAWN_SLOT_LIFE        0x10
#define AREA_SPAWN_SLOT_RADIUS      0x100
#define AREA_SPAWN_SLOT_CORE_SHADE  0x40
#define AREA_SPAWN_SLOT_RADIUS_STEP 0x10
void        func_801F4D44(void);
void        func_801F5050(u8 level);
extern void func_801F5940(void);

extern u8 D_8014554C[];

extern u8 D_80146865;
extern u8 D_80146875;

void func_801F40D0(s32 arg0);
void func_801F42E8(void);

void func_801F40A4(void);
void func_801F46EC(void* arg0, s32 arg1, s32 arg2);
s32  func_801F4E7C(void);

void func_801F48E8(void* arg0, void* arg1, s32 arg2);
void func_801F4BC0(void* slot);
void func_801F4DBC(s32 arg0);
void func_801F5580(s32 arg0);

#endif

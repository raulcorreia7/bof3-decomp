#ifndef OVERLAY_WORLD02_AREA098_13_H
#define OVERLAY_WORLD02_AREA098_13_H

/* The world02/area098/13 overlay: one file per split function
 * and its data. Only this image includes the file. */

#include "overlays/area/world02.h"
#include "area/spad.h"

/* The work-window byte offset and row stride this overlay scans. */
#define SCRATCH_ROW_OFFSET    0x00
#define SCRATCH_ROW_STRIDE    0x1C

/* The work-window byte offset, row stride and row count this overlay clears. */
#define SCRATCH_COLUMN_OFFSET 0
#define SCRATCH_COLUMN_STRIDE 0x18
#define SCRATCH_COLUMN_COUNT  8

#include "shared/WorldSpin.h"

#define AREA_SPIN_RADIUS     16
#define AREA_SPIN_PITCH      (RANDOM_MASK(0x7FF) - 0x400)
#define AREA_SPIN_SCALE_MASK 0x2
#define AREA_SPIN_SCALE_BASE 3
#define AREA_SPIN_FADE       0x20

extern Callback D_801F5F68[];
extern Callback D_801F5F7C[];
extern Callback D_801F5F88[];
extern Callback D_801F5FAC[];
extern void (*D_801F5FBC[])(void* slot);

/* The screen-capture size for one table row. */
typedef struct CaptureSize {
    s16 w;
    s16 h;
    s16 unk_04[2];
} CaptureSize;

/* One of the 16 slots at AREA_WORK, 0x1C bytes each. */
typedef struct AreaBurstSlot {
    u8  active; /* 0x00 - 0 marks a free slot */
    u8  kind;   /* 0x01 - selects the per-frame handler */
    u8  life;   /* 0x02 - frames left */
    u8  fade;   /* 0x03 */
    u8  unk_04; /* 0x04 */
    u8  unk_05[3];
    s32 speed;    /* 0x08 */
    s32 unk_0C;   /* 0x0C */
    s32 distance; /* 0x10 */
    s32 unk_14;   /* 0x14 */
    s32 unk_18;   /* 0x18 */
} AreaBurstSlot;

ASSERT_SIZE(AreaBurstSlot, 0x1C);

/* One of the slots at AREA_WORK, 0x38 bytes each: a streak drawn between two points. */
typedef struct AreaStreakSlot {
    u8  active;     /* 0x00 - 0 marks a free slot */
    u8  kind;       /* 0x01 */
    u8  life;       /* 0x02 */
    u8  head_shade; /* 0x03 - shade at the first point */
    u8  tail_shade; /* 0x04 - shade at the second point */
    u8  unk_05[3];
    s32 head[3]; /* 0x08 */
    s32 unk_14;
    s32 tail[3]; /* 0x18 */
    u8  unk_24[0x14];
} AreaStreakSlot;

ASSERT_SIZE(AreaStreakSlot, 0x38);

extern u8 D_801F6510;
extern u8 D_801F6514;

/* The per-image spawn step Area_UpdateSpawn runs between the slot claim and the slot pass. */
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
void func_801F4220(AreaStreakSlot* slot);
u8   func_801F42E8(void);
void func_801F4490(WorldPos* pos, s32 vx, s32 vy);

void func_801F40A4(void);
void func_801F46EC(void* arg0, s32 arg1, s32 arg2);
s32  func_801F4E7C(void);

void func_801F48E8(void* arg0, void* arg1, s32 arg2);
void func_801F4BC0(AreaBurstSlot* slot);
void func_801F4FEC(AreaBurstSlot* slot);
void func_801F4DBC(AreaBurstSlot* slot);
void func_801F5580(s32 arg0);

extern u8          D_801F6520;
extern CaptureSize D_801F5F5C[];

#endif

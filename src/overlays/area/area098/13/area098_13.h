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
    s32 unk_24;
    s32 vel[3]; /* 0x28 */
    s32 unk_34;
} AreaStreakSlot;

ASSERT_SIZE(AreaStreakSlot, 0x38);

extern u8 D_801F6510;
extern u8 D_801F6514;

/* One point of the spark trail at AREA_WORK + 0x2000, 10 bytes each. */
typedef struct TrailDot {
    u8  active; /* 0x00 - flips every frame it is processed */
    u8  life;   /* 0x01 */
    u16 color;  /* 0x02 - 5-5-5 */
    s16 x;      /* 0x04 */
    s16 y;      /* 0x06 */
    s8  dx;     /* 0x08 */
    s8  dy;     /* 0x09 */
} TrailDot;

ASSERT_SIZE(TrailDot, 10);

/* The trail points at AREA_WORK + 0x2000. */
#define AREA_TRAIL_DOTS MEM_PTR(TrailDot, AREA_WORK + 0x2000u)

extern u16 D_801F651C;

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

void func_801F40D0(s32 unused);
void func_801F4220(AreaStreakSlot* slot);
u8   func_801F42E8(void);
void func_801F4490(WorldPos* pos, s32 orange_radius, s32 black_radius);

void func_801F40A4(void);
void GFX_DrawColorFan(s32* pos, s16 origin, s32 flags);
s32  func_801F4E7C(void);

/* func_801F48E8 */
void Area_DrawYellowLine(s32* from, s32* to, u8 intensity);
void func_801F4BC0(AreaBurstSlot* slot);
void func_801F4FEC(AreaBurstSlot* slot);
void func_801F4DBC(AreaBurstSlot* slot);
void func_801F5580(s32 arg0);

/* One row of the screen-capture table: the region the trail dots copy from. */
typedef struct CaptureRect {
    u16 x; /* 0x0 */
    u16 y; /* 0x2 */
    s16 w; /* 0x4 */
    s16 h; /* 0x6 */
} CaptureRect;

ASSERT_SIZE(CaptureRect, 8);

extern u8          D_801F6520;
extern CaptureRect D_801F5F58[];

#endif

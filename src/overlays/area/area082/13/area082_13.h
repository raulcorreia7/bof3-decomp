#ifndef OVERLAY_WORLD02_AREA082_13_H
#define OVERLAY_WORLD02_AREA082_13_H

/* The world02/area082/13 overlay: one file per split function
 * and its data. Only this image includes the file. */

#include "overlays/area/world02.h"
#include "area/spad.h"
#include "area/effects.h"

/* The gate keeper's two refusals: the Patriarch's permission and the holy
 * ground's special permission. */
#define AREA082_MSG_NEED_PATRIARCH_PERMISSION 3
#define AREA082_MSG_NEED_SPECIAL_PERMISSION   8

/* The work-window byte offset, row stride and row count this overlay clears. */
#define SCRATCH_COLUMN_OFFSET                 0
#define SCRATCH_COLUMN_STRIDE                 0x14
#define SCRATCH_COLUMN_COUNT                  0x80

extern u8 D_801F5734[];

/* One ring point: the x and y byte offsets from the effect origin. */
typedef struct RingOffset {
    s8 x;
    s8 y;
} RingOffset;

ASSERT_SIZE(RingOffset, 0x02);
ASSERT_OFFSET(RingOffset, y, 0x01);

extern RingOffset D_801F5764[];
extern Callback   D_801F576C[];

void func_801F3500(void);
u8   Area_StepSparks(void);
void func_801F4430(void);
void func_801F5388(s32 scale);

void func_801F5428(s32 colors);

extern Callback D_801F57D0[];

/* Set while the ramp reaches its end colour. */
extern u8 D_8014933A;

extern u8 D_80145EED[3];

/* func_801F393C */
void Area_AddSpark(void);
void func_801F2F50(Pos3* pos, s16 a, s16 b, u16 c, s32 d, s32 e);
void func_801F46C8(s32 arg0, s32 arg1, s32 arg2, s32 arg3);

#endif

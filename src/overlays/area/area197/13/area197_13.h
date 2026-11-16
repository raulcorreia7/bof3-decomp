#ifndef OVERLAY_WORLD04_AREA197_13_H
#define OVERLAY_WORLD04_AREA197_13_H

/* The world04/area197/13 overlay: one file per split function
 * and its data. Only this image includes the file. */

#include "overlays/area/world04.h"
#include "area/spad.h"

/* The scratchpad work row and the published record the step paths read. */

/* The character work record, viewed as bytes here. */

/* The area-flag bit store. */
extern s8                  D_80146874;
extern s8                  D_80146875;
/* D_801F4A2C */
extern PartyMemberMessages g_PartyMemberMessages[7];
/* The state handler banks the step dispatchers index. */
extern u8                  D_801F431C[];
extern Callback            D_801F4368[];
extern Callback            D_801F4A80[];
/* The two-byte step table the falling path indexes. */
extern s8                  D_801F4A88[];

/* The image's step passes. */
void func_801F3768(s32 arg0, s32 arg1);
void func_801F30E4(void);
void func_801F3474(void);
void func_801F3110(u16 start, u16 end, Point3l* from, Point3l* to);

s32 func_801F2FC4(void);
s32 func_801F3368(void);

/* One of the 128 falling sparks at AREA_WORK: it falls, bounces off the ground and fades out. */
typedef struct AreaSparkRow {
    u8      active; /* 0x00 - 0 marks a free spark */
    u8      unk_01; /* 0x01 */
    u8      life;   /* 0x02 - frames left; clears the spark at 0 */
    u8      shade;  /* 0x03 - fades to black as the spark dies */
    u8      frame;  /* 0x04 - indexes the draw routine's corner table */
    u8      pad_05[3];
    s32     vx; /* 0x08 */
    s32     vy; /* 0x0C */
    s32     vz; /* 0x10 - the fall speed and the bounce */
    u8      pad_14[4];
    Point3l pos;       /* 0x18 */
    u8      pad_24[4]; /* 0x24 */
} AreaSparkRow;

ASSERT_SIZE(AreaSparkRow, 0x28);
ASSERT_OFFSET(AreaSparkRow, pos, 0x18);

/* The seeded sparks' launch speed, lifetime and shade; the dropped rows fall
 * twice as fast. */
#define AREA_SPARK_SPEED     0x1000
#define AREA_DROP_SPEED      0x2000
#define AREA_SPARK_LIFE_BASE 0x18
#define AREA_SPARK_SHADE     0x48

/* The triangle rows func_801F2E74 offsets the projected point by: the second
 * and third vertex relative to the first, in screen space. */
typedef struct AreaTriangleOffset {
    u16 dx1;
    u16 dy1;
    u16 dx2;
    u16 dy2;
} AreaTriangleOffset;

ASSERT_SIZE(AreaTriangleOffset, 8);

extern AreaTriangleOffset D_801F4328[];

void func_801F2E74(AreaSparkRow* spark);

/* The dropped sparks follow the sparks at AREA_WORK. */
#define AREA_SPARK_ROW_COUNT 128
#define AREA_DROP_COUNT      128
#define AREA_DROP_ROWS       (AREA_WORK + AREA_SPARK_ROW_COUNT * sizeof(AreaSparkRow))

/* One dropped spark: it falls and bounces like an AreaSparkRow. */
typedef struct AreaDropRow {
    u8      active; /* 0x00 - 0 marks a free row */
    u8      unk_01; /* 0x01 */
    u8      life;   /* 0x02 - frames left */
    u8      shade;  /* 0x03 */
    s32     vx;     /* 0x04 */
    s32     vy;     /* 0x08 */
    s32     vz;     /* 0x0C */
    u8      pad_10[4];
    Point3l pos; /* 0x14 */
    u8      pad_20[4];
} AreaDropRow;

ASSERT_SIZE(AreaDropRow, 0x24);
ASSERT_OFFSET(AreaDropRow, pos, 0x14);

void func_801F32A4(Actor* actor);

#endif

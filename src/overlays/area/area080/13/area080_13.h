#ifndef OVERLAY_WORLD02_AREA080_13_H
#define OVERLAY_WORLD02_AREA080_13_H

/* The world02/area080/13 overlay: one file per split function
 * and its data. Only this image includes the file. */

#include "overlays/area/world02.h"
#include "area/spad.h"

#define AREA_SPARK_TRAIL_POINTS 4u

/* One of the eight sparks the area keeps after the ring in its work area:
 * it drifts by its velocity and settles on the ground. */
typedef struct AreaSparkSlot {
    u8       active;                                /* 0x00 */
    u8       life;                                  /* 0x01 - frames left; the slot frees at 0 */
    u8       pad_02[2];                             /* 0x02 */
    CVECTOR  color;                                 /* 0x04 */
    s32      velocity_x;                            /* 0x08 */
    s32      velocity_y;                            /* 0x0C */
    s32      velocity_z;                            /* 0x10 */
    u8       pad_14[4];                             /* 0x14 */
    WorldPos origin;                                /* 0x18 - where the spark starts */
    u8       pad_24[4];                             /* 0x24 */
    WorldPos pos;                                   /* 0x28 */
    u8       pad_34[0xC];                           /* 0x34 */
    DVECTOR  origin_trail[AREA_SPARK_TRAIL_POINTS]; /* 0x40 */
    DVECTOR  pos_trail[AREA_SPARK_TRAIL_POINTS];    /* 0x50 */
} AreaSparkSlot;

ASSERT_SIZE(AreaSparkSlot, 0x60);
ASSERT_OFFSET(AreaSparkSlot, color, 0x04);
ASSERT_OFFSET(AreaSparkSlot, velocity_x, 0x08);
ASSERT_OFFSET(AreaSparkSlot, velocity_z, 0x10);
ASSERT_OFFSET(AreaSparkSlot, origin, 0x18);
ASSERT_OFFSET(AreaSparkSlot, pos, 0x28);
ASSERT_OFFSET(AreaSparkSlot, origin_trail, 0x40);
ASSERT_OFFSET(AreaSparkSlot, pos_trail, 0x50);

#define AREA_SPARK_SLOT_COUNT 8u
#define g_AreaSparks          ((AreaSparkSlot*)(AREA_WORK + sizeof(AreaRing)))

extern WorldPos       D_80146954;
extern u8             D_801F3DAC[];
extern u16            D_801F4494[];
extern u16            D_801F4498[];
extern u16            D_801F449C[];
extern AreaRing*      D_801F44A0;
extern AreaSparkSlot* D_801F44A4;

/* func_801F30B0 */
void Area_ProjectRing(AreaRing* ring);
void func_801F31A0(s32 arg0);
void func_801F33DC(AreaRing* ring);
/* func_801F352C */
void Area_DrawSpark(AreaSparkSlot* spark);
void func_801F3834(void);
void func_801F3870(void);

void func_801F395C(void);

#endif

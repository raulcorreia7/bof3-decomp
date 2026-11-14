#ifndef SHARED_AREA_SPARK_H
#define SHARED_AREA_SPARK_H

#include "common/vector.h"

/* One of the 128 falling sparks at AREA_WORK: the walkers fall it by its speed
 * each frame and clear it below the actor's ground height. */
typedef struct AreaSpark {
    u8      active;     /* 0x00 - 0 marks a free spark */
    u8      unk_01;     /* 0x01 */
    s16     fall_speed; /* 0x02 - 16.8 fall per frame */
    Point3l pos;        /* 0x04 */
    s32     unk_10;     /* 0x10 */
} AreaSpark;

#define AREA_SPARK_COUNT 128

ASSERT_SIZE(AreaSpark, 0x14);
ASSERT_OFFSET(AreaSpark, active, 0x00);
ASSERT_OFFSET(AreaSpark, unk_01, 0x01);
ASSERT_OFFSET(AreaSpark, fall_speed, 0x02);
ASSERT_OFFSET(AreaSpark, pos, 0x04);
ASSERT_OFFSET(AreaSpark, unk_10, 0x10);

#endif

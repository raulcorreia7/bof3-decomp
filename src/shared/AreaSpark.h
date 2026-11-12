#ifndef SHARED_AREA_SPARK_H
#define SHARED_AREA_SPARK_H

#include "common/vector.h"

/* One of the 128 falling sparks at the area work base. */
typedef struct AreaSpark {
    u8       active;
    u8       unk_01;
    s16      fall_speed;
    Point3DL pos;
    s32      unk_10;
} AreaSpark;

ASSERT_OFFSET(AreaSpark, unk_01, 0x01);
ASSERT_OFFSET(AreaSpark, pos, 0x04);
ASSERT_SIZE(AreaSpark, 0x14);

#endif

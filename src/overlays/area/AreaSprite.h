#ifndef OVERLAY_AREA_SPRITE_H
#define OVERLAY_AREA_SPRITE_H

#include "common/vector.h"
#include "psx/psyq.h"

typedef struct AreaSprite {
    u8      flags;
    u8      flags_01;
    u8      flags_02;
    u8      flags_03;
    Point3l origin;
    u8      unk_10[4];
    VECTOR  normal;
    u16     half_size;
} AreaSprite;

ASSERT_SIZE(AreaSprite, 0x28);
ASSERT_OFFSET(AreaSprite, origin, 0x04);
ASSERT_OFFSET(AreaSprite, normal, 0x14);
ASSERT_OFFSET(AreaSprite, half_size, 0x24);

#endif

#ifndef OVERLAY_AREA_SPRITE_H
#define OVERLAY_AREA_SPRITE_H

#include "common/vector.h"
#include "psx/psyq.h"

typedef struct AreaSprite {
    u8     flags;
    u8     stage;
    u8     count;
    u8     tick;
    Pos3   origin;
    u8     unk_10[4];
    VECTOR normal;
    u16    half_size;
    u8     unk_26;
} AreaSprite;

ASSERT_OFFSET(AreaSprite, origin, 0x04);
ASSERT_OFFSET(AreaSprite, normal, 0x14);
ASSERT_OFFSET(AreaSprite, half_size, 0x24);
ASSERT_OFFSET(AreaSprite, unk_26, 0x26);
ASSERT_SIZE(AreaSprite, 0x28);

#endif

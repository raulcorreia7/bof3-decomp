#include "area067_14.h"

MATCH void func_801F3D54(s16* row) {
    AreaRippleQuad* quad;
    u16             angle;
    s16             radius;
    s16             y;

    quad   = (AreaRippleQuad*)&SELF(Actor)->vx;
    angle  = rand() & 0xFC0;
    radius = rand() & 0x38;
    row[0] = quad->x + ((radius * rcos(angle)) >> 12);
    y      = quad->y + ((radius * rsin(angle)) >> 13);
    row[4] = 0;
    row[2] = 0;
    row[3] = 0;
    row[6] = 0x20;
    row[1] = y;
    row[5] = y;
}

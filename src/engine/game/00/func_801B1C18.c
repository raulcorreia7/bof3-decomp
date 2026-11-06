#include "game_00.h"

MATCH s32 func_801B1C18(s32 x, s32 y, s32 mode) {
    s16 value;
    s32 i;
    s32 px;
    s32 py;
    s32 span_x;
    s32 span_y;
    s8  dir_x;
    s8  dir_y;

    span_x = abs(x - D_80145EC4) >> 15;
    span_y = abs(y - D_80145EC8) >> 15;
    if ((x >> 16) > D_80145EC6) {
        dir_x = 1;
    } else {
        dir_x = -((x >> 16) < D_80145EC6);
    }
    if ((y >> 16) > D_80145ECA) {
        dir_y = 1;
    } else {
        dir_y = -((y >> 16) < D_80145ECA);
    }
    for (i = 0; i <= span_x; i++) {
        /* The tracked height cell is the s16 at +0xA of the pair base; both
         * probes read it through the pair they walk, hence the two offsets. */
        px    = FIELD(s32, &D_80145EC4, 0) + dir_x * (i << 15);
        value = Area_ReadHeight(px, y);
        if (abs(FIELD(s16, &D_80145EC4, 0xA) - value) >= 0x41) {
            return 0;
        }
        if (func_801C3E40(px, y, mode & BYTE_MASK, value) & BYTE_MASK) {
            return 0;
        }
    }
    for (i = 0; i <= span_y; i++) {
        py    = FIELD(s32, &D_80145EC8, 0) + dir_y * (i << 15);
        value = Area_ReadHeight(x, py);
        if (abs(FIELD(s16, &D_80145EC8, 0x6) - value) >= 0x41) {
            return 0;
        }
        if (func_801C3E40(x, py, mode & BYTE_MASK, value) & BYTE_MASK) {
            return 0;
        }
    }
    return 1;
}

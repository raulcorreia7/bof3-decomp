#include "game_00.h"

MATCH s16 func_801BDCF8(s32 x, s32 y) {
    s16 value;
    s16 limit;
    s32 delta;

    value = Area_SampleHeight(x, y);
    limit = COORD_INT(g_Task->z);
    delta = limit;
    delta -= value;
    delta = ABS(delta);
    delta = delta < 0x101;
    if (!delta) {
        value = limit;
    }
    return value;
}

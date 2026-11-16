#include "area077_14.h"

#ifdef NON_MATCHING
/* Appends the banner's leading point to the trail and returns the point's sine offset. */
NON_MATCHING s16 func_801F35E0(s32 arg0, s32 arg1, s16 arg2, s16 arg3, s16 arg4, s16 arg5) {
    s16      y;
    s8       i;
    Point2s* current;
    s16      offset;
    s32      angle;
    Point2s* next;

    i       = 0x22;
    next    = MEM_PTR(Point2s, AREA_WORK + 4);
    current = MEM_PTR(Point2s, AREA_WORK);
    do {
        next[i] = current[i];
        i--;
    } while (i >= 0);

    MEM(s16, AREA_WORK)     = arg0 + 4 + arg2;
    angle                   = ((s16)arg3 << 4) * (arg2 - arg5 - 0x20);
    if (angle < 0) {
        angle += 0x3F;
    }
    offset                  = ((s16)arg4 * rsin((u16)((u32)angle >> 6))) >> 12;
    y                       = offset + 0x24;
    MEM(s16, AREA_WORK + 2) = arg1 + y;
    return offset;
}
#else
INCLUDE_ASM(func_801F35E0);
#endif

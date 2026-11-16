#include "area077_14.h"

#ifdef NON_MATCHING
/* Appends the banner's leading point to the trail and returns the point's sine offset. */
NON_MATCHING s16 func_801F35E0(s32 origin_x, s32 origin_y, s16 scroll_x, s16 scroll_y, s16 radius, s16 focus_x) {
    Pos2* current;
    Pos2* next;
    s16   offset;
    s16   y;
    s32   angle;
    s8    i;

    i       = 0x22;
    next    = MEM_PTR(Pos2, AREA_WORK + 4);
    current = MEM_PTR(Pos2, AREA_WORK);
    do {
        next[i] = current[i];
        i--;
    } while (i >= 0);

    MEM(s16, AREA_WORK) = origin_x + 4 + scroll_x;
    angle               = ((s16)scroll_y << 4) * (scroll_x - focus_x - 0x20);
    if (angle < 0) {
        angle += 0x3F;
    }
    offset                  = ((s16)radius * rsin((u16)((u32)angle >> 6))) >> 12;
    y                       = offset + 0x24;
    MEM(s16, AREA_WORK + 2) = origin_y + y;
    return offset;
}
#else
INCLUDE_ASM(func_801F35E0);
#endif

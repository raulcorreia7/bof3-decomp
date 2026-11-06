#include "game_00.h"

/* nonmatching 94.41%: branch@+0x0000; the case arms still differ in tail scheduling. */
#ifdef NON_MATCHING
NON_MATCHING s32 func_801A1C5C(s32 x, s32 y, s32 route, s32 unused) {
    /* FAKE: register pins reproduce retail's s2/s4/s0/s5/s1/s3 assignment; pinned 94.41%. */
    MATCH_REG(s32, sx, "s2");
    s32 sy;
    /* FAKE: pins continue the assignment from the note above. */
    MATCH_REG(s32, sum, "s0");
    MATCH_REG(s32, part, "s5");
    s32 xhi;
    MATCH_REG(s32, yhi, "s3");
    char y_low;
    s32  xcell;
    s32  ycell;
    s32  cell;
    s16  y_low_word;
    sx = x;
    sy = y;
    switch (route & 0xFF) {
        case 1:
            xhi   = sx >> 16;
            yhi   = ((u32)sy) >> 16;
            y_low = yhi;
            sum   = func_801A20F8(xhi & 0xFFFF, y_low);
            part  = sum + func_801A20F8((xhi + 1) & 0xFFFF, y_low);
            sum   = part;
            if (!(sx & 0xFFFF)) {
                sum = part + func_801A20F8((xhi - 1) & 0xFFFF, y_low);
            }
            sum += (func_801A21EC(sx, sy) + func_801A21EC(sx + 0x8000, sy)) + func_801A21EC(sx - 0x8000, sy);
            break;

        case 5:
            if (sy & 0xFFFF) {
                xcell = sx >> 16;
                ycell = ((sy >> 16) + 1) & 0xFFFF;
                sum   = func_801A20F8(xcell & 0xFFFF, ycell);
                part  = sum + func_801A20F8((xcell + 1) & 0xFFFF, ycell);
                sum   = part;
                if (!(sx & 0xFFFF)) {
                    sum = part + func_801A20F8((xcell - 1) & 0xFFFF, ycell);
                }
            } else {
                xhi  = sx >> 16;
                yhi  = ((u32)sy) >> 16;
                sum  = func_801A20F8(xhi & 0xFFFF, yhi);
                part = sum + func_801A20F8((xhi + 1) & 0xFFFF, yhi);
                sum  = part;
                if (!(sx & 0xFFFF)) {
                    sum = part + func_801A20F8((xhi - 1) & 0xFFFF, yhi);
                }
            }
            sum += (func_801A21EC(sx, sy) + func_801A21EC(sx + 0x8000, sy)) + func_801A21EC(sx - 0x8000, sy);
            break;

        case 3:
            if (sx & 0xFFFF) {
                cell = ((sx >> 16) + 1) & 0xFFFF;
            } else {
                cell = ((u32)sx) >> 16;
            }
            /* cases 3 and 7 share the y-axis accumulation. */
            goto check_y;

        case 7:
            cell = ((u32)sx) >> 16;
        check_y:
            yhi = sy >> 16;

            sum        = func_801A20F8(cell, yhi & 0xFFFF);
            y_low_word = yhi;
            part       = sum + func_801A20F8(cell, (y_low_word + 1) & 0xFFFF);
            sum        = part;
            if (!(sy & 0xFFFF)) {
                sum = part + func_801A20F8(cell, (y_low_word - 1) & 0xFFFF);
            }
            sum += (func_801A21EC(sx, sy) + func_801A21EC(sx, sy + 0x8000)) + func_801A21EC(sx, sy - 0x8000);
            break;

        default:
            sum = 1;
            break;
    }

    return (sum & 0xFF) != 0;
}
#else
/* First difference: the case-3 branch target. */
INCLUDE_ASM(func_801A1C5C);
#endif

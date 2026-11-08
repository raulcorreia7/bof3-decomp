#include "game_00.h"

/* nonmatching 84.06%: branch@+0x0044; the default arm and the call-result accumulation still differ. */
#ifdef NON_MATCHING
NON_MATCHING s32 func_801A1ED8(s32 x, s32 y, s32 route, s32 unused) {
    /* FAKE: register pins reproduce retail's s1/s2/s0/s3/s4 assignment; pinned 84.06%. */
    FAKE_REG(s32, sx, "s1");
    FAKE_REG(s32, sy, "s2");
    /* FAKE: pins continue the assignment from the note above. */
    FAKE_REG(s32, result, "s0");
    FAKE_REG(s32, s3, "s3");
    /* FAKE: pin continues the assignment from the note above. */
    FAKE_REG(s32, s4, "s4");
    sx = x;
    sy = y;
    switch (route & BYTE_MASK) {
        case FACING_UP:
            s3     = (s16)(sx >> 16);
            s4     = ((u32)sy) >> 16;
            result = func_801A20F8(s3 & HALF_MASK, s4);
            if (sx & HALF_MASK) {
                result += (func_801A20F8((s3 + 1) & HALF_MASK, s4) + func_801A223C(sx & 0xFFFF0000, sy)) +
                          func_801A223C(sx + 0x8000, sy);
            }
            break;

        case FACING_DOWN:
            if (sy & HALF_MASK) {
                s4     = (s16)(sx >> 16);
                s3     = ((sy >> 16) + 1) & HALF_MASK;
                result = func_801A20F8(s4 & HALF_MASK, s3);
                if (sx & HALF_MASK) {
                    s3 = ((sy >> 16) + 1) & HALF_MASK;
                    result += (func_801A20F8((s4 + 1) & HALF_MASK, s3) + func_801A223C(sx & 0xFFFF0000, sy)) +
                              func_801A223C(sx + 0x8000, sy);
                }
            } else {
                s3     = (s16)(sx >> 16);
                s4     = ((u32)sy) >> 16;
                result = func_801A20F8(s3 & HALF_MASK, s4);
                if (sx & HALF_MASK) {
                    result += (func_801A20F8((s3 + 1) & HALF_MASK, s4) + func_801A223C(sx & 0xFFFF0000, sy)) +
                              func_801A223C(sx + 0x8000, sy);
                }
            }
            break;

        case FACING_RIGHT:
            if (sx & HALF_MASK) {
                s4 = ((sx >> 16) + 1) & HALF_MASK;
            } else {
                s4 = ((u32)sx) >> 16;
            }
            /* cases 3 and 7 share the y-axis accumulation. */
            goto body_7;

        case FACING_LEFT:
            s4 = ((u32)sx) >> 16;
        body_7:
            s3 = (s16)(sy >> 16);

            result = func_801A20F8(s4, s3 & HALF_MASK);
            if (sy & HALF_MASK) {
                result += (func_801A20F8(s4, (s3 + 1) & HALF_MASK) + func_801A223C(sx, sy & 0xFFFF0000)) +
                          func_801A223C(sx, sy + 0x8000);
            }
            break;

        default:
            return 1;
    }

    result += func_801A21EC(sx, sy);
    return (result & BYTE_MASK) != 0;
}
#else
INCLUDE_ASM(func_801A1ED8);
#endif

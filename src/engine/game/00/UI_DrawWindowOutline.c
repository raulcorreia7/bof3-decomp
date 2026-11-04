#include "game_00.h"

/* draws the outline of the rectangle at (x, y) of width by height in the window style color; bit 0 of flags picks the blend
 * of the edge pieces and bits 4-7 cut the four corners. */
/* nonmatching unmeasured: tried 65.09%: byte-based color table index fixed; retail colors computed first in s4/s3/s1,
 * args copied to s8/s7/s5 (pins reach correct set but lose 8 points); no sh a0,0x28(sp) arg spill in retail. */
#ifdef NON_MATCHING
NON_MATCHING void UI_DrawWindowOutline(s16 x, s16 y, s16 width, s32 height, s32 flags) {
    u16 stack_20[4];
    s16 val0;
    s16 val1;
    s16 val2;
    s16 val3;
    s16 val4;
    s32 tmp0;
    s32 tmp1;
    s32 tmp2;
    s32 val5;
    s32 val6;
    s32 val7;
    s32 val8;
    s32 val9;
    s32 val10;
    s32 val11;
    u16 tmp3;
    u32 tmp4;

    val11 = 2;
    val0  = x;
    val4  = y;
    val2  = width;
    tmp3  = *(u16*)(((D_80144952 << 6) | 0x20) + (u8*)&D_80033A08);
    tmp4  = tmp3 & HALF_MASK;
    tmp1  = flags & 1;
    if (tmp1 == 0) {
        val11 = 1;
    }
    val8 = 1;
    if (tmp1 == 0) {
        val8 = 2;
    }
    val6 = 1;
    val5 = 0;
    do {
        tmp2 = val5 & BYTE_MASK;
        if (val6 & ((u32)(flags & BYTE_MASK) >> 4)) {
            stack_20[tmp2] = 3;
        } else {
            stack_20[tmp2] = 0;
        }
        val5 += 1;
        val6 *= 2;
    } while ((u32)(val5 & BYTE_MASK) < 4U);
    val10 = ((tmp3 & 0x1F) * 8) & BYTE_MASK;
    val9  = (tmp4 >> 2) & 0xF8 & BYTE_MASK;
    val7  = (tmp4 >> 7) & 0xF8 & BYTE_MASK;
    tmp0  = val11 & BYTE_MASK;
    val3  = val4 + height;
    GFX_DrawLine(val0, (s16)(val4 + stack_20[0]), val0, (s16)(val3 - (stack_20[2] + 1)), (u8)val10, (u8)val9, (u8)val7,
                 tmp0);
    if ((s16)stack_20[0] != 0) {
        GFX_DrawLine(val0, (s16)(val3 - (stack_20[2] + 1)), (s16)(val0 + stack_20[2]), val3, (u8)val10, (u8)val9,
                     (u8)val7, val8);
    }
    val1 = val3;
    val8 &= BYTE_MASK;
    val2 += val0;
    GFX_DrawLine((s16)(val0 + stack_20[2]), val1, (s16)(val2 - (stack_20[3] + 1)), val1, (u8)val10, (u8)val9, (u8)val7,
                 val8);
    if (stack_20[1] != 0) {
        GFX_DrawLine((s16)(val2 - (stack_20[3] + 1)), val1, val2, (s16)(val3 - stack_20[3]), (u8)val10, (u8)val9,
                     (u8)val7, val8);
    }
    val1 = val2;
    GFX_DrawLine(val1, (s16)(val3 - stack_20[3]), val1, (s16)(val4 + ((u16)stack_20[1] + 1)), (u8)val10, (u8)val9,
                 (u8)val7, val8);
    if ((s16)stack_20[2] != 0) {
        GFX_DrawLine(val1, (s16)(val4 + ((u16)stack_20[1] + 1)), (s16)(val2 - (u16)stack_20[1]), val4, (u8)val10,
                     (u8)val9, (u8)val7, tmp0);
    }
    val1 = val4;
    GFX_DrawLine((s16)(val2 - (u16)stack_20[1]), val1, (s16)(val0 + (stack_20[0] + 1)), val1, (u8)val10, (u8)val9,
                 (u8)val7, tmp0);
    if ((s16)stack_20[3] != 0) {
        GFX_DrawLine((s16)(val0 + (stack_20[0] + 1)), val1, val0, (s16)(val4 + stack_20[0]), (u8)val10, (u8)val9,
                     (u8)val7, tmp0);
    }
}
#else
INCLUDE_ASM(UI_DrawWindowOutline);
#endif

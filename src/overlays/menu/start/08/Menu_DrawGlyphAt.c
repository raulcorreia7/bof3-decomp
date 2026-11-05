#include "start_08.h"

/* nonmatching unmeasured: tried the first draft cleaned to compiling C; best score 55.84%. resume: a lever or header fix that
 * closes the first mismatch. */
#ifdef NON_MATCHING
NON_MATCHING u8* Menu_DrawGlyphAt(s16 x, s16 y, s32 color, u8* cursor, s32 glyph_left, s32 glyph_right) {
    s32       stack_18;
    s32       stack_20;
    s16       tmp0;
    s16       tmp1;
    s16       tmp2;
    s16       tmp3;
    s16       tmp4;
    s16       tmp5;
    s16       val0;
    s16       val1;
    s16       val2;
    s16       val3;
    s32       val4;
    s32       val5;
    s32       val6;
    s32       val7;
    s32       val8;
    s32       val9;
    u16       val10;
    POLY_FT4* val11;
    u8*       val12;
    u8        tmp6;
    u8        tmp7;
    u8        tmp8;
    u8        tmp9;
    u8        tmp10;
    u8        tmp11;
    u8        tmp12;
    u8        tmp13;
    u8        tmp14;
    u8        tmp15;
    u8        tmp16;
    u8        tmp17;
    u8        tmp18;
    u8        tmp19;
    u8        tmp20;
    u8        tmp21;
    u8        tmp22;
    u8        val13;

    val2     = x;
    val3     = y;
    val12    = cursor;
    val7     = glyph_left;
    stack_18 = color;
    stack_20 = glyph_right;
    func_801E3E34(0U);
    val11 = (POLY_FT4*)g_GfxPrimCursor;
    SetPolyFT4(val11);
    val1  = val2;
    val0  = val3;
    tmp21 = *val12;
    val13 = (u8)stack_20;
    val6  = val7;
    if ((s32)tmp21 < 0x14) {
        if ((s32)tmp21 < 0x12) {
            if ((s32)tmp21 < 2) {
                val9 = val13 & BYTE_MASK;
                if ((s32)tmp21 >= 0) {
                    return val12 + 1;
                }
                goto block_11; /* retail branch */
            }
            val9 = val13 & BYTE_MASK;
            goto block_11; /* retail branch */
        }
        val12 += 1;
        tmp3      = val2 + ((val13 & BYTE_MASK) - (val6 & BYTE_MASK));
        tmp0      = val3 + 0xC;
        val11->x0 = val1;
        val11->y0 = val0;
        val11->x1 = tmp3;
        val11->y1 = val0;
        val11->x2 = val1;
        val11->y2 = tmp0;
        val11->x3 = tmp3;
        val11->y3 = tmp0;
        tmp6      = *val12;
        val11->u0 = (s8)(val7 + (((tmp6 % 21) & BYTE_MASK) * 0xC));
        tmp17     = *val12;
        val11->v0 = (s8)(((tmp17 / 21) & BYTE_MASK) * 0xC);
        tmp7      = *val12;
        val11->u1 = (s8)(stack_20 + (((tmp7 % 21) & BYTE_MASK) * 0xC));
        tmp18     = *val12;
        val11->v1 = (s8)(((tmp18 / 21) & BYTE_MASK) * 0xC);
        tmp8      = *val12;
        val11->u2 = (s8)(val7 + (((tmp8 % 21) & BYTE_MASK) * 0xC));
        tmp14     = *val12;
        val11->v2 = (s8)((((tmp14 / 21) & BYTE_MASK) * 0xC) + 0xC);
        tmp9      = *val12;
        val11->u3 = (s8)((((tmp9 % 21) & BYTE_MASK) * 0xC) + stack_20);
        tmp19     = *val12;
        setRGB0(val11, 128, 128, 128);
        val11->v3 = (s8)((((tmp19 / 21) & BYTE_MASK) * 0xC) + 0xC);
        val10     = GetClut((stack_18 & 0xF) * 16, 480);
        val5      = 0x100;
        goto block_16; /* retail branch */
    }
    if (tmp21 != 0x15) {
        val9 = val13 & BYTE_MASK;
        if (tmp21 == GAME_NONE) {
            return val12 + 1;
        }
    block_11:
        tmp4      = val1 + (val9 - (val6 & BYTE_MASK));
        tmp1      = val0 + 0xC;
        val11->x0 = val1;
        val11->y0 = val0;
        val11->x1 = tmp4;
        val11->y1 = val0;
        val11->x2 = val1;
        val11->y2 = tmp1;
        val11->x3 = tmp4;
        val11->y3 = tmp1;
        tmp13     = *val12;
        if (tmp13 < 0x5BU) {
            val11->u0 = (s8)(val6 + (((tmp13 % 21) & BYTE_MASK) * 0xC));
            tmp20     = *val12;
            val11->v0 = (s8)(((tmp20 / 21) & BYTE_MASK) * 0xC);
            tmp10     = *val12;
            val11->u1 = (s8)(val13 + (((tmp10 % 21) & BYTE_MASK) * 0xC));
            tmp22     = *val12;
            val11->v1 = (s8)(((tmp22 / 21) & BYTE_MASK) * 0xC);
            tmp11     = *val12;
            val11->u2 = (s8)(val6 + (((tmp11 % 21) & BYTE_MASK) * 0xC));
            tmp15     = *val12;
            val11->v2 = (s8)((((tmp15 / 21) & BYTE_MASK) * 0xC) + 0xC);
            tmp12     = *val12;
            val11->u3 = (s8)(val13 + (((tmp12 % 21) & BYTE_MASK) * 0xC));
            tmp16     = *val12;
            val8      = ((tmp16 / 21) & BYTE_MASK) * 3;
        } else {
            val11->v0 = (s8)(((*val12 + 0x23) / 21) * 0xC);
            val11->u0 = (s8)(val6 + (((tmp13 + 0x23) % 21) * 0xC));
            val11->u1 = (s8)(val13 + (((*val12 + 0x23) % 21) * 0xC));
            val11->v1 = (s8)(((*val12 + 0x23) / 21) * 0xC);
            val11->u2 = (s8)(val6 + (((*val12 + 0x23) % 21) * 0xC));
            val11->v2 = (s8)((((*val12 + 0x23) / 21) * 0xC) + 0xC);
            val11->u3 = (s8)(val13 + (((*val12 + 0x23) % 21) * 0xC));
            val8      = ((*val12 + 0x23) / 21) * 3;
        }
        val11->v3 = (s8)((val8 * 4) + 0xC);
        val4      = (stack_18 & 0xF) * 0x10;
        setRGB0(val11, 128, 128, 128);
        goto block_15; /* retail branch */
    }
    val12 += 1;
    tmp5      = val2 + ((val13 & BYTE_MASK) - (val6 & BYTE_MASK));
    tmp2      = val3 + 0xC;
    val11->x0 = val1;
    val11->y0 = val0;
    val11->x1 = tmp5;
    val11->y1 = val0;
    val11->x2 = val1;
    val11->y2 = tmp2;
    val11->x3 = tmp5;
    val11->y3 = tmp2;
    val11->u0 = (s8)(val7 + (((*val12 + 0x64) % 21) * 0xC));
    val11->v0 = (s8)(((*val12 + 0x64) / 21) * 0xC);
    val11->u1 = (s8)(stack_20 + (((*val12 + 0x64) % 21) * 0xC));
    val11->v1 = (s8)(((*val12 + 0x64) / 21) * 0xC);
    val11->u2 = (s8)(val7 + (((*val12 + 0x64) % 21) * 0xC));
    val11->v2 = (s8)((((*val12 + 0x64) / 21) * 0xC) + 0xC);
    val11->u3 = (s8)((((*val12 + 0x64) % 21) * 0xC) + stack_20);
    val4      = (stack_18 & 0xF) * 0x10;
    setRGB0(val11, 128, 128, 128);
    val11->v3 = (s8)((((*val12 + 0x64) / 21) * 0xC) + 0xC);
block_15:
    val10 = GetClut(val4, 480);
    val5  = 0;
block_16:
    val11->clut  = val10;
    val11->tpage = GetTPage(0, 1, 960, val5);
    GFX_AddPrim(1U, 0x28U);
    return val12 + 1;
}
#else
/* nonmatching 55.84%: first difference +0x0 retail addiu sp,sp,-0x50 against candidate -0x40 (0xA4C against 0x9F8);
 * retail spills three values at 0x10/0x18/0x20, the draft two. resume: add the (u8)color local retail keeps at 0x10($sp)
 * (stored at +0x70, read byte-wise only by the block_11 clut tail at 0x801E3DB0; the 0x12/0x13 tail uses the s32 color
 * at 0x18), then restate the shared POLY_FT4 fill (0x12/0x13 no offset unsigned, 0x15 +0x64 signed, 0x5B +0x23 signed). */
INCLUDE_ASM(Menu_DrawGlyphAt);
#endif

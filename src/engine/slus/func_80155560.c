#include "engine/slus/slus.h"

/* Lifted draft; semantics are unverified. */
#ifdef NON_MATCHING
NON_MATCHING s32 func_80155560(u32 part_word, void* prim, s32 mode) {
    s16       uv[4][4];
    s16       tmp0;
    s16       tmp1;
    s16       tmp2;
    s16       val0;
    s16       val1;
    s32       tmp3;
    s32       tmp4;
    s32       tmp5;
    s32       tmp6;
    s32       tmp7;
    s32       tmp8;
    s32       valid;
    s32       val3;
    s32       val4;
    s32       val5;
    s32       val6;
    s8        tmp9;
    s8        val7;
    u16       tmp10;
    u16       tmp11;
    u16       tmp12;
    u16       tmp13;
    u32       val8;
    s32       val9;
    void*     val10;
    s32       val11;
    void*     tmp14;
    void*     tmp15;
    void*     tmp16;
    POLY_FT4* poly;

    val8  = part_word;
    val10 = prim;
    val11 = mode;
    valid = (s32)val8 >> 0x1F;
    valid = valid == 0;
    val9  = ((s32)val8 >> 0x1C) & 3;
    if (val8 & 0xF00) {
        if (val8 & 0x800) {
            tmp14    = (*((val9 * 4) + &g_AreaMapBundle.tile_table_offsets_04[0][1]) * 4) + (((val8 & 0x7FF) * 8) + (MAP_BUNDLE_BASE + 0x00));
            uv[0][0] = FIELD(s8, tmp14, 0x3u);
            uv[0][1] = FIELD(s16, tmp14, 0x2u) & BYTE_MASK;
            uv[1][0] = FIELD(u8, tmp14, 0x1u);
            tmp15    = tmp14 + 4;
            uv[1][1] = (u16) * (u8*)(tmp14);
            uv[2][0] = FIELD(s8, tmp15, 0x3u);
            uv[2][1] = FIELD(s16, tmp15, 0x2u) & BYTE_MASK;
            uv[3][0] = FIELD(u8, tmp15, 0x1u);
            uv[3][1] = FIELD(u8, tmp14, 0x4u);
        } else {
            tmp16    = (*((val9 * 4) + &g_AreaMapBundle.tile_table_offsets_04[0][0]) * 4) + (((val8 & BYTE_MASK) * 4) + (MAP_BUNDLE_BASE + 0x00));
            tmp9     = FIELD(s8, tmp16, 0x3u);
            uv[2][0] = (s16)tmp9;
            uv[0][0] = (s16)tmp9;
            tmp12    = FIELD(s16, tmp16, 0x2u) & BYTE_MASK;
            uv[1][1] = tmp12;
            uv[0][1] = tmp12;
            tmp1     = tmp9 + FIELD(u8, tmp16, 0x1u);
            uv[3][0] = tmp1;
            uv[1][0] = tmp1;
            tmp11    = tmp12 + *(u8*)(tmp16);
            uv[3][1] = tmp11;
            uv[2][1] = tmp11;
        }
    } else {
        tmp2     = (val8 & 0xF) * 0x10;
        tmp0     = tmp2 | 0xF;
        tmp13    = val8 & 0xF0;
        tmp10    = tmp13 | 0xF;
        uv[2][0] = tmp2;
        uv[0][0] = tmp2;
        uv[1][1] = tmp13;
        uv[0][1] = tmp13;
        uv[3][0] = tmp0;
        uv[1][0] = tmp0;
        uv[3][1] = tmp10;
        uv[2][1] = tmp10;
    }
    if (val8 & 0x40000) {
        tmp3     = (s32)uv[0][0];
        uv[0][0] = (s32)uv[2][0];
        uv[2][0] = (s32)uv[3][0];
        uv[3][0] = (s32)uv[1][0];
        uv[1][0] = tmp3;
    }
    if (val8 & 0x10000) {
        tmp6     = uv[1][0];
        uv[1][0] = uv[0][0];
        tmp4     = uv[2][0];
        uv[0][0] = tmp6;
        uv[2][0] = uv[3][0];
        uv[3][0] = tmp4;
    }
    val3 = (s32)val8 >> 0x18;
    if (val8 & 0x20000) {
        tmp7     = uv[2][0];
        uv[2][0] = uv[0][0];
        tmp5     = uv[1][0];
        uv[0][0] = tmp7;
        uv[1][0] = uv[3][0];
        uv[3][0] = tmp5;
        val3     = (s32)val8 >> 0x18;
    }
    tmp8 = val3 & 0xF;
    val1 = ((tmp8 * valid) + 0x1E3) << 6;
    val7 = ((s32)val8 >> 0x10) & 0xF8;
    if (valid == 0) {
        val1 |= tmp8;
    }
    val5 = valid & 3;
    if ((GetGraphType() == 1) || (val5 = valid & 3, (GetGraphType() == 2))) {
        val6 = (val5 << 9) | (((s32)val8 >> 5) & 0x180);
        val4 = ((s32)((val9 << 7) + SCREEN_WIDTH) >> 6) | 0x20;
    } else {
        val6 = (val5 << 7) | (((s32)val8 >> 7) & 0x60);
        val4 = ((s32)((val9 << 7) + SCREEN_WIDTH) >> 6) | 0x10;
    }
    val0 = val6 | val4;
    val9 = 0;
    if (val11 > 0) {
        poly = (POLY_FT4*)val10;
        do {
            SetSemiTrans(poly, ((s32)val8 >> 0xF) & 1);
            poly->b0    = val7;
            poly->g0    = val7;
            poly->r0    = val7;
            poly->clut  = val1;
            poly->tpage = val0;
            poly->u0    = (u8)uv[0][0];
            poly->v0    = (u8)uv[0][1];
            poly->u1    = (u8)uv[1][0];
            poly->v1    = (u8)uv[1][1];
            poly->u2    = (u8)uv[2][0];
            poly->v2    = (u8)uv[2][1];
            poly->u3    = (u8)uv[3][0];
            val9 += 1;
            poly->v3 = (u8)uv[3][1];
            val4     = val9 < val11;
            poly++;
        } while (val4 != 0);
    }
    return val4;
}
#else
INCLUDE_ASM(func_80155560);
#endif

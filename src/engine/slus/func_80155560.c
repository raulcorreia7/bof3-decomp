#include "engine/slus/slus.h"

/* Lifted draft; semantics are unverified. */
#ifdef NON_MATCHING
NON_MATCHING s32 func_80155560(u32 part_word, void* prim, s32 mode) {
    s16       u0, v0, u1, v1, u2, v2, u3, v3;
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
            tmp14 = (*((val9 * 4) + &g_AreaMapBundle.tile_table_offsets_04[0][1]) * 4) + (((val8 & 0x7FF) * 8) + (MAP_BUNDLE_BASE + 0x00));
            u0    = FIELD(s8, tmp14, 0x3u);
            v0    = FIELD(s16, tmp14, 0x2u) & BYTE_MASK;
            u1    = FIELD(u8, tmp14, 0x1u);
            tmp15 = tmp14 + 4;
            v1    = (u16) * (u8*)(tmp14);
            u2    = FIELD(s8, tmp15, 0x3u);
            v2    = FIELD(s16, tmp15, 0x2u) & BYTE_MASK;
            u3    = FIELD(u8, tmp15, 0x1u);
            v3    = FIELD(u8, tmp14, 0x4u);
        } else {
            tmp16 = (*((val9 * 4) + &g_AreaMapBundle.tile_table_offsets_04[0][0]) * 4) + (((val8 & BYTE_MASK) * 4) + (MAP_BUNDLE_BASE + 0x00));
            tmp9  = FIELD(s8, tmp16, 0x3u);
            u2    = (s16)tmp9;
            u0    = (s16)tmp9;
            tmp12 = FIELD(s16, tmp16, 0x2u) & BYTE_MASK;
            v1    = tmp12;
            v0    = tmp12;
            tmp1  = tmp9 + FIELD(u8, tmp16, 0x1u);
            u3    = tmp1;
            u1    = tmp1;
            tmp11 = tmp12 + *(u8*)(tmp16);
            v3    = tmp11;
            v2    = tmp11;
        }
    } else {
        tmp2  = (val8 & 0xF) * 0x10;
        tmp0  = tmp2 | 0xF;
        tmp13 = val8 & 0xF0;
        tmp10 = tmp13 | 0xF;
        u2    = tmp2;
        u0    = tmp2;
        v1    = tmp13;
        v0    = tmp13;
        u3    = tmp0;
        u1    = tmp0;
        v3    = tmp10;
        v2    = tmp10;
    }
    if (val8 & 0x40000) {
        tmp3 = (s32)u0;
        u0   = (s32)u2;
        u2   = (s32)u3;
        u3   = (s32)u1;
        u1   = tmp3;
    }
    if (val8 & 0x10000) {
        tmp6 = u1;
        u1   = u0;
        tmp4 = u2;
        u0   = tmp6;
        u2   = u3;
        u3   = tmp4;
    }
    val3 = (s32)val8 >> 0x18;
    if (val8 & 0x20000) {
        tmp7 = u2;
        u2   = u0;
        tmp5 = u1;
        u0   = tmp7;
        u1   = u3;
        u3   = tmp5;
        val3 = (s32)val8 >> 0x18;
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
            poly->u0    = (u8)u0;
            poly->v0    = (u8)v0;
            poly->u1    = (u8)u1;
            poly->v1    = (u8)v1;
            poly->u2    = (u8)u2;
            poly->v2    = (u8)v2;
            poly->u3    = (u8)u3;
            val9 += 1;
            poly->v3 = (u8)v3;
            val4     = val9 < val11;
            poly++;
        } while (val4 != 0);
    }
    return val4;
}
#else
INCLUDE_ASM(func_80155560);
#endif

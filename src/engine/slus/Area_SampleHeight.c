#include "engine/slus/slus.h"

/* samples the bundle's four-corner cell records and height bytes at the 16.16 point (x, y): the half-cell
 * bits pick the corner formula, D_80149340 scales the height byte (cleared by the caller), and the result is the
 * larger diagonal sum * 16 or, with both half-cell bits, the largest corner * 32, as s16; outside the grid it returns
 * 0.
 */
/* nonmatching unmeasured: tried the first draft cleaned to compiling C; register pins dropped, score is the pinned draft; best
 * score 82.69%. resume: a lever or header fix that closes the first mismatch. */
#ifdef NON_MATCHING
NON_MATCHING s16 Area_SampleHeight(s32 x, s32 y) {
    s8   v[4];
    s32  tmp0;
    s32  tmp1;
    s32  tmp2;
    s32  tmp3;
    s32  tmp4;
    s32  tmp5;
    s32  tmp6;
    s32  tmp7;
    s32  tmp8;
    s32  tmp9;
    s8*  tmp10;
    u16  fx;
    u16  fy;
    u32  bad;
    u32* tmp11;
    u32  tmp12;
    s32  mw;
    u8*  tmp13;
    u8*  tmp14;
    u8*  base;

    tmp5 = x;
    tmp6 = y;
    base = MEM_PTR(u8, (MAP_BUNDLE_BASE + 0x00));
    tmp8 = tmp5 >> 0x10;
    mw   = *(u8*)base;
    tmp9 = tmp6 >> 0x10;
    bad  = ((u32)tmp8 >> 0x1F);
    bad |= (tmp8 >= (s32)mw);
    bad |= ((u32)tmp9 >> 0x1F);
    bad |= (tmp9 >= (s32)g_AreaMapBundle.height_01);
    if (bad != 0) {
        return 0;
    }
    tmp6 &= ~0x7FFF;
    fy   = (u16)tmp6;
    tmp3 = (tmp6 >> 0x10) * mw;
    tmp5 &= ~0x7FFF;
    fx    = (u16)tmp5;
    tmp1  = tmp5 >> 0x10;
    tmp14 = (u8*)((tmp1 * 4) + ((tmp3 * 4) + (MAP_BUNDLE_BASE + 0x30)));
    tmp13 = (u8*)((g_AreaMapBundle.height_off4_2A * 4) + (tmp1 + base) + tmp3);
    if (!((tmp5 | tmp6) & HALF_MASK)) {
        tmp4  = *(s8*)(tmp13)*D_80149340;
        tmp12 = *(u32*)(tmp14);
        return (s16)((((s32)(tmp12 << 0x10) >> 0x18) + tmp4 + ((s32)(tmp12 << 8) >> 0x18) + tmp4) * 0x10);
    }
    tmp7  = mw * 4;
    tmp11 = (u32*)(tmp14 + tmp7);
    tmp10 = (s8*)(tmp13 + mw);
    if (fx != fy) {
        if (fx != 0) {
            v[0] = ((u32) * (u32*)(tmp14) >> 8) + (*(s8*)(tmp13)*D_80149340);
            v[1] = FIELD(u8, tmp14, 0x3u) + (*(s8*)(tmp13)*D_80149340);
            v[2] = FIELD(s32, tmp14, 0x4u) + (FIELD(s8, tmp13, 0x1u) * D_80149340);
            v[3] = FIELD(u16, tmp14, 0x6u) + (FIELD(s8, tmp13, 0x1u) * D_80149340);
        } else {
            v[0] = FIELD(u16, tmp14, 0x2u) + (*(s8*)(tmp13)*D_80149340);
            v[1] = FIELD(u8, tmp14, 0x3u) + (*(s8*)(tmp13)*D_80149340);
            v[2] = *tmp11 + (*tmp10 * D_80149340);
            v[3] = (u16)((u32)*tmp11 >> 8) + (*tmp10 * D_80149340);
        }
        tmp2 = v[0] + v[1];
        tmp0 = v[2] + v[3];
        if (tmp0 < tmp2) {
            return tmp2 * 0x10;
        }
        return tmp0 * 0x10;
    }
    v[0] = FIELD(u8, tmp14, 0x3u) + (*(s8*)(tmp13)*D_80149340);
    v[1] = FIELD(u16, tmp14, 0x6u) + (FIELD(s8, tmp13, 0x1u) * D_80149340);
    v[2] = FIELD(s32, (tmp7 + tmp14), 0x4u) + (FIELD(s8, (mw + tmp13), 0x1u) * D_80149340);
    v[3] = ((u32)*tmp11 >> 8) + (*tmp10 * D_80149340);
    if ((v[0] >= v[1]) & (v[0] >= v[2]) & (v[0] >= v[3])) {
        return v[0] << 5;
    }
    if ((v[1] >= v[2]) & (v[1] >= v[3])) {
        return v[1] << 5;
    }
    if (v[2] < v[3]) {
        return v[3] << 5;
    }
    return v[2] << 5;
}
#else
INCLUDE_ASM(Area_SampleHeight);
#endif

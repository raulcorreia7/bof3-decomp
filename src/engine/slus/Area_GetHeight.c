#include "engine/slus/slus.h"

/* lifted draft, best score 46.74%; semantics unverified
 */
/* func_80154ABC */
#ifdef NON_MATCHING
NON_MATCHING s32 Area_GetHeight(s32 x, s32 y, u8 mode) {
    s8   sp[4];
    s32  tmp0;
    s32  tmp1;
    s32  tmp2;
    s32  tmp3;
    s32  tmp4;
    s32  tmp5;
    s32  tmp6;
    s32  tmp7;
    s32  tmp8;
    s32  val0;
    s32  val1;
    s32  val2;
    s32  val3;
    s8*  tmp9;
    s8   tmp10;
    s8   tmp11;
    s8   tmp12;
    s8   tmp13;
    s8   tmp14;
    s8   val4;
    s8   val5;
    u16  val6;
    u32* tmp15;
    u32  tmp16;
    u32  tmp17;
    u32  tmp18;
    u32  tmp19;
    u8*  tmp20;
    u8   tmp21;
    u8   val7;
    u8*  tmp22;
    u8*  tmp23;

    tmp7  = x >> 0x10;
    tmp21 = MEM(u8, (MAP_BUNDLE_BASE + 0x00));
    tmp8  = y >> 0x10;
    {
        u8 map_h = g_AreaMapBundle.height;
        if ((((u32)tmp7 >> 0x1F) | (tmp7 >= (s32)tmp21) | ((u32)tmp8 >> 0x1F) | (tmp8 >= (s32)map_h)) != 0) {
            SP_REF(s8, 0x0) = 0;
            return 0;
        }
    }
    tmp5  = y & ~0x7FFF;
    tmp2  = (tmp5 >> 0x10) * tmp21;
    tmp4  = x & ~0x7FFF;
    tmp0  = tmp4 >> 0x10;
    tmp23 = (u8*)((tmp0 * 4) + ((tmp2 * 4) + (MAP_BUNDLE_BASE + 0x30)));
    tmp22 = (u8*)((g_AreaMapBundle.height_off4_2A * 4) + (tmp0 + (MAP_BUNDLE_BASE + 0x00)) + tmp2);
    if (!((tmp4 | tmp5) & HALF_MASK)) {
        SP_REF(void*, 0x0) = 0;
        tmp3               = *(s8*)(tmp22)*g_AreaHeightOffsetEnabled;
        tmp19              = *(u32*)(tmp23);
        val3               = (((s32)(tmp19 << 0x10) >> 0x18) + tmp3 + ((s32)(tmp19 << 8) >> 0x18) + tmp3) << 0x14;
        goto block_23; /* retail branch */
    }
    tmp6  = tmp21 * 4;
    tmp15 = (u32*)(tmp23 + tmp6);
    tmp1  = tmp4 & HALF_MASK;
    tmp9  = (s8*)(tmp22 + tmp21);
    if (tmp1 != (tmp5 & HALF_MASK)) {
        if (tmp1 != 0) {
            sp[0] = ((u32) * (u32*)(tmp23) >> 8) + (*(s8*)(tmp22)*g_AreaHeightOffsetEnabled);
            sp[1] = FIELD(u8, tmp23, 0x3u) + (*(s8*)(tmp22)*g_AreaHeightOffsetEnabled);
            sp[2] = FIELD(s32, tmp23, 0x4u) + (FIELD(s8, tmp22, 0x1u) * g_AreaHeightOffsetEnabled);
            val0  = FIELD(s8, tmp22, 0x1u) * g_AreaHeightOffsetEnabled;
            val6  = FIELD(u16, tmp23, 0x6u);
        } else {
            sp[0] = FIELD(u16, tmp23, 0x2u) + (*(s8*)(tmp22)*g_AreaHeightOffsetEnabled);
            sp[1] = FIELD(u8, tmp23, 0x3u) + (*(s8*)(tmp22)*g_AreaHeightOffsetEnabled);
            sp[2] = *tmp15 + (*tmp9 * g_AreaHeightOffsetEnabled);
            val0  = *tmp9 * g_AreaHeightOffsetEnabled;
            val6  = (u16)((u32)*tmp15 >> 8);
        }
        sp[3] = val6 + val0;
        if ((sp[0] == sp[2]) & (sp[1] == sp[3])) {
            SP_REF(void*, 0x0) = 0;
            return (sp[0] + sp[1]) * 0x10;
        }
        SP_REF(void*, 0x0) = 1;
        val1               = (sp[0] + sp[1]) - (sp[2] + sp[3]);
        val1               = ABS(val1);
        val3               = val1 << 0x14;
        goto block_23; /* retail branch */
    }
    tmp11 = FIELD(u8, tmp23, 0x3u) + (*(s8*)(tmp22)*g_AreaHeightOffsetEnabled);
    sp[0] = tmp11;
    tmp13 = FIELD(u16, tmp23, 0x6u) + (FIELD(s8, tmp22, 0x1u) * g_AreaHeightOffsetEnabled);
    sp[1] = tmp13;
    tmp10 = FIELD(s32, (tmp6 + tmp23), 0x4u) + (FIELD(s8, (tmp21 + tmp22), 0x1u) * g_AreaHeightOffsetEnabled);
    sp[2] = tmp10;
    tmp12 = ((u32)*tmp15 >> 8) + (*tmp9 * g_AreaHeightOffsetEnabled);
    sp[3] = tmp12;
    if ((tmp11 == tmp13) & (tmp11 == tmp10) & (tmp11 == tmp12)) {
        SP_REF(void*, 0x0) = 0;
        return tmp11 << 5;
    }
    SP_REF(void*, 0x0) = 1;
    tmp17              = mode & BYTE_MASK;
    if (mode & 1) {
        tmp16 = tmp17 >> 1;
        tmp20 = (u8*)(sp + tmp16);
        val7  = *tmp20;
        tmp14 = *(sp + ((tmp16 + 1) & 3));
        if ((s8)*tmp20 < tmp14) {
            val7 = (u8)tmp14;
        }
        val5 = *(sp + ((tmp16 + 2) & 3));
        val4 = (s8)val7;
    } else {
        tmp18 = tmp17 >> 1;
        val4  = *(sp + tmp18);
        val5  = *(sp + ((tmp18 + 2) & 3));
    }
    val2 = val4 - val5;
    val2 = ABS(val2);
    val3 = val2 << 0x15;
block_23:
    return (s16)(val3 >> 0x10);
}
#else
INCLUDE_ASM(Area_GetHeight);
#endif

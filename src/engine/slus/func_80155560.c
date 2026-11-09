#include "engine/slus/slus.h"

/* lifted draft, best score 23.25%; semantics unverified
 */
#ifdef NON_MATCHING
NON_MATCHING s32 func_80155560(u32 part_word, void* prim, s32 mode) {
    s16   stack_18; /* compiler-managed */
    u16   stack_1A;
    s16   stack_20; /* compiler-managed */
    u16   stack_22;
    s16   stack_28; /* compiler-managed */
    u16   stack_2A;
    s16   stack_30; /* compiler-managed */
    u16   stack_32;
    s16   tmp0;
    s16   tmp1;
    s16   tmp2;
    s16   val0;
    s16   val1;
    s32   tmp3;
    s32   tmp4;
    s32   tmp5;
    s32   tmp6;
    s32   tmp7;
    s32   tmp8;
    s32   val2;
    s32   val3;
    s32   val4;
    s32   val5;
    s32   val6;
    s8    tmp9;
    s8    val7;
    u16   tmp10;
    u16   tmp11;
    u16   tmp12;
    u16   tmp13;
    u32   val8;
    s32   val9;
    void* val10;
    s32   val11;
    void* tmp14;
    void* tmp15;
    void* tmp16;

    val8  = part_word;
    val10 = prim;
    val11 = mode;
    val2  = (s32)val8 >> 0x1F;
    val2  = val2 == 0;
    val9  = ((s32)val8 >> 0x1C) & 3;
    if (val8 & 0xF00) {
        if (val8 & 0x800) {
            tmp14    = (*((val9 * 4) + &g_AreaMapBundle.tile_table_offsets_04[0][1]) * 4) + (((val8 & 0x7FF) * 8) + (MAP_BUNDLE_BASE + 0x00));
            stack_18 = FIELD(s8, tmp14, 0x3u);
            stack_1A = FIELD(s16, tmp14, 0x2u) & BYTE_MASK;
            stack_20 = FIELD(u8, tmp14, 0x1u);
            tmp15    = tmp14 + 4;
            stack_22 = (u16) * (u8*)(tmp14);
            stack_28 = FIELD(s8, tmp15, 0x3u);
            stack_2A = FIELD(s16, tmp15, 0x2u) & BYTE_MASK;
            stack_30 = FIELD(u8, tmp15, 0x1u);
            stack_32 = FIELD(u8, tmp14, 0x4u);
        } else {
            tmp16    = (*((val9 * 4) + &g_AreaMapBundle.tile_table_offsets_04[0][0]) * 4) + (((val8 & BYTE_MASK) * 4) + (MAP_BUNDLE_BASE + 0x00));
            tmp9     = FIELD(s8, tmp16, 0x3u);
            stack_28 = (s16)tmp9;
            stack_18 = (s16)tmp9;
            tmp12    = FIELD(s16, tmp16, 0x2u) & BYTE_MASK;
            stack_22 = tmp12;
            stack_1A = tmp12;
            tmp1     = tmp9 + FIELD(u8, tmp16, 0x1u);
            stack_30 = tmp1;
            stack_20 = tmp1;
            tmp11    = tmp12 + *(u8*)(tmp16);
            stack_32 = tmp11;
            stack_2A = tmp11;
        }
    } else {
        tmp2     = (val8 & 0xF) * 0x10;
        tmp0     = tmp2 | 0xF;
        tmp13    = val8 & 0xF0;
        tmp10    = tmp13 | 0xF;
        stack_28 = tmp2;
        stack_18 = tmp2;
        stack_22 = tmp13;
        stack_1A = tmp13;
        stack_30 = tmp0;
        stack_20 = tmp0;
        stack_32 = tmp10;
        stack_2A = tmp10;
    }
    if (val8 & 0x40000) {
        tmp3     = (s32)stack_18;
        stack_18 = (s32)stack_28;
        stack_28 = (s32)stack_30;
        stack_30 = (s32)stack_20;
        stack_20 = tmp3;
    }
    if (val8 & 0x10000) {
        tmp6     = stack_20;
        stack_20 = stack_18;
        tmp4     = stack_28;
        stack_18 = tmp6;
        stack_28 = stack_30;
        stack_30 = tmp4;
    }
    val3 = (s32)val8 >> 0x18;
    if (val8 & 0x20000) {
        tmp7     = stack_28;
        stack_28 = stack_18;
        tmp5     = stack_20;
        stack_18 = tmp7;
        stack_20 = stack_30;
        stack_30 = tmp5;
        val3     = (s32)val8 >> 0x18;
    }
    tmp8 = val3 & 0xF;
    val1 = ((tmp8 * val2) + 0x1E3) << 6;
    val7 = ((s32)val8 >> 0x10) & 0xF8;
    if (val2 == 0) {
        val1 |= tmp8;
    }
    val5 = val2 & 3;
    if ((GetGraphType() == 1) || (val5 = val2 & 3, (GetGraphType() == 2))) {
        val6 = (val5 << 9) | (((s32)val8 >> 5) & 0x180);
        val4 = ((s32)((val9 << 7) + SCREEN_WIDTH) >> 6) | 0x20;
    } else {
        val6 = (val5 << 7) | (((s32)val8 >> 7) & 0x60);
        val4 = ((s32)((val9 << 7) + SCREEN_WIDTH) >> 6) | 0x10;
    }
    val0 = val6 | val4;
    val9 = 0;
    if (val11 > 0) {
        val2 = (s32)val10;
        do {
            SetSemiTrans((void*)val2, ((s32)val8 >> 0xF) & 1);
            FIELD(s8, val2, 0x6u)   = val7;
            FIELD(s8, val2, 0x5u)   = val7;
            FIELD(s8, val2, 0x4u)   = val7;
            FIELD(s16, val2, 0xEu)  = val1;
            FIELD(s16, val2, 0x16u) = val0;
            FIELD(s8, val2, 0xCu)   = (s8)(u16)stack_18;
            FIELD(s8, val2, 0xDu)   = (s8)stack_1A;
            FIELD(s8, val2, 0x14u)  = (s8)(u16)stack_20;
            FIELD(s8, val2, 0x15u)  = (s8)stack_22;
            FIELD(s8, val2, 0x1Cu)  = (s8)(u16)stack_28;
            FIELD(s8, val2, 0x1Du)  = (s8)stack_2A;
            FIELD(s8, val2, 0x24u)  = (s8)(u16)stack_30;
            val9 += 1;
            FIELD(s8, val2, 0x25u) = (s8)stack_32;
            val4                   = val9 < val11;
            val2 += 0x28;
        } while (val4 != 0);
    }
    return val4;
}
#else
INCLUDE_ASM(func_80155560);
#endif

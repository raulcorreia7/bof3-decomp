#include "engine/slus/slus.h"

/* lifted draft, best score 45.34%; semantics unverified
 */
#ifdef NON_MATCHING
NON_MATCHING void func_80157CE4(u8* record, s32 cell_x, s32 cell_y) {
    u16   stack_28;
    s16   stack_2A;
    s16   stack_2C;
    u16   stack_30;
    s16   stack_32;
    s16   stack_34;
    u16   stack_38;
    s16   stack_3A;
    s16   stack_3C;
    u16   stack_40;
    s16   stack_42;
    s16   stack_44;
    s32   stack_48;
    s32   stack_4C;
    s16   tmp0;
    s16   val0;
    s16   val1;
    s16   val2;
    s32   tmp1;
    s32   tmp2;
    s32   tmp3;
    s32   tmp4;
    s32   tmp5;
    s32   tmp6;
    s32   tmp7;
    s32   tmp8;
    s32   val3;
    s32   val4;
    s8    tmp9;
    s8    tmp10;
    u16   val5;
    u32   tmp11;
    u32   val6;
    u8**  val7;
    void* tmp12;
    void* val8;

    val5  = cell_x;
    tmp11 = (u32)(FIELD(u8, record, 0x3u) - 0x3F) >> 1;
    val0  = cell_y;
    if ((s32)tmp11 < 4) {
        val3 = 1;
        val6 = tmp11;
    } else {
        val3 = 2;
        val6 = (tmp11 - 4) * 2;
    }
    tmp5     = val0 * g_AreaMapBundle.width;
    tmp7     = val5 * 4;
    val5     = (val5 << 7) - 0x4040;
    stack_38 = val5;
    stack_28 = val5;
    val0     = (val0 << 7) - 0x4040;
    stack_3A = val0;
    stack_2A = val0;
    val8     = tmp7 + ((tmp5 * 4) + (MAP_BUNDLE_BASE + 0x30));
    if (val3 > 0) {
        do {
            val7 = &g_GfxPrimCursor;
            val7 = (u8**)g_GfxPrimCursor;
            SetPolyFT4((POLY_FT4*)val7);
            SetShadeTex(val7, 0);
            tmp2     = val6 & 1;
            stack_40 = val5;
            if (tmp2 == 0) {
                stack_40 = val5 + 0x80;
            }
            tmp0     = val0 + (tmp2 << 7);
            stack_42 = tmp0;
            stack_32 = tmp0;
            stack_30 = stack_40;
            if (tmp2 != 0) {
                tmp8  = FIELD(s32, (val8), -4);
                tmp10 = *(s8*)(val8);
                tmp4  = (s32)(tmp8 << 0x10) >> 0x18;
                val2  = tmp4 * 0x10;
                if (tmp10 >= tmp4) {
                    if (((s32)((s32) * (s8*)(val8) << 8) >> 0x18) < (tmp8 >> 0x18)) {
                        val2 = tmp4 * 0x10;
                        goto block_10; /* retail branch */
                    }
                    stack_3C = -(tmp10 * 0x10);
                    val4     = (s32)(FIELD(u16, val8, 0x2u) << 0x18) >> 0x14;
                } else {
                block_10:
                    stack_3C = -val2;
                    val4     = FIELD(s8, (val8), -1) * 0x10;
                }
            } else {
                tmp9  = *(s8*)(val8);
                tmp12 = val8 - (g_AreaMapBundle.width * 4);
                tmp6  = *(s32*)(tmp12);
                tmp3  = (s32)(tmp6 << 8) >> 0x18;
                val1  = tmp3 * 0x10;
                if ((tmp9 < tmp3) || (val1 = tmp3 * 0x10, ((((s32)((s32) * (s8*)(val8) << 0x10) >> 0x18) < (tmp6 >> 0x18)) != 0))) {
                    stack_3C = -val1;
                    val4     = (s32)(FIELD(u8, tmp12, 0x3u) << 0x18) >> 0x14;
                } else {
                    stack_3C = -(tmp9 * 0x10);
                    val4     = ((s32)((s32) * (s8*)(val8) << 0x10) >> 0x18) * 0x10;
                }
            }
            stack_44 = (s16)-val4;
            val3 -= 1;
            stack_2C = (u16)stack_3C - 0x80;
            stack_34 = (u16)stack_44 - 0x80;
            RotTransPers4((SVECTOR*)&stack_28, (SVECTOR*)&stack_30, (SVECTOR*)&stack_38, (SVECTOR*)&stack_40, (s32*)(val7 + 8), (s32*)(val7 + 0x10), (s32*)(val7 + 0x18), (s32*)(val7 + 0x20),
                          &stack_48, &stack_4C);
            tmp1 = D_8017F8E0[val6];
            val6 += 1;
            func_80155560((u32)tmp1, val7, 1);
            GFX_AddPrim((u32)g_AreaDrawMode, sizeof(POLY_FT4));
        } while (val3 > 0);
    }
}
#else
INCLUDE_ASM(func_80157CE4);
#endif

#include "engine/slus/slus.h"

/* lifted draft, best score 63.72%; semantics unverified
 */
#ifdef NON_MATCHING
NON_MATCHING void func_801569B8(u8* record, s32 cell_x, s32 cell_y) {
    s32      stack_28;
    s32      stack_2C;
    SVECTOR* val0;
    s16      tmp0;
    s16      tmp1;
    s16      tmp2;
    s16      tmp3;
    s16      val1;
    s32      tmp4;
    s32      tmp5;
    s32      tmp6;
    s32      tmp7;
    s32      val2;
    s32      val3;
    s32      val4;
    s32      val5;
    s32      val6;
    s32      val7;
    s32      val8;
    u8**     val9;

    (void)record;
    val4 = cell_x;
    val5 = cell_y;
    tmp7 = -(Area_SampleHeight((val4 - 1) << 0x10, val5 << 0x10) / 2);
    val4 = (val4 - 0x81) << 7;
    val5 = (val5 - 0x80) << 7;
    val3 = 0;
    val0 = D_1F800014;
    val0 = D_1F800014;
    val7 = g_FrameCount & 7;
    val1 = (s16)tmp7 - (val7 * 8);
    val6 = val7;
    do {
        val9 = &g_GfxPrimCursor;
        val9 = (u8**)g_GfxPrimCursor;
        SetPolyFT4((POLY_FT4*)val9);
        SetShadeTex(val9, 0);
        tmp6              = RANDOM_MASK(3);
        val8              = 0x10 - ((u32)(g_FrameCount & 0x1FFF) >> 8);
        val8              = ABS(val8);
        SP_REF(s16, 0x18) = val1;
        SP_REF(s16, 0x20) = val1;
        SP_REF(s16, 0x28) = val1;
        SP_REF(s16, 0x30) = val1;
        tmp4              = (val7 * 4) + ((val3 << 5) + 0x20) + tmp6;
        tmp5              = (val6 * val8) / 10;
        tmp1              = (val4 - tmp4) + tmp5;
        tmp2              = (val5 - tmp4) - tmp5;
        tmp3              = val4 + tmp4 + tmp5;
        tmp0              = (val5 + tmp4) - tmp5;
        D_1F800014[0].vx  = tmp1;
        SP_REF(s16, 0x16) = tmp2;
        D_1F800014[1].vx  = tmp3;
        SP_REF(s16, 0x1E) = tmp2;
        D_1F800014[2].vx  = tmp1;
        SP_REF(s16, 0x26) = tmp0;
        D_1F800014[3].vx  = tmp3;
        SP_REF(s16, 0x2E) = tmp0;
        RotTransPers4(&D_1F800014[1], &D_1F800014[2], &D_1F800014[3], &D_1F800014[0], (s32*)(val9 + 0x10),
                      (s32*)(val9 + 0x18), (s32*)(val9 + 0x20), (s32*)(val9 + 8), &stack_28, &stack_2C);
        val2 = (((7 - val3) * 8) + 7) - val7;
        if (val2 < 0) {
            val2 += 3;
        }
        func_80155560(((val2 >> 2) << 0x13) | 0xBA009124, val9, 1);
        val1 -= 0x40;
        val6 += 8;
        val3 += 1;
        GFX_AddPrim((u32)g_AreaDrawMode, sizeof(POLY_FT4));
    } while (val3 < 8);
}
#else
INCLUDE_ASM(func_801569B8);
#endif

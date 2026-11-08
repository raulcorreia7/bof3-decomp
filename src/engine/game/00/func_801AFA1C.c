#include "game_00.h"

/* nonmatching unmeasured: saved regs s6/s7 swapped (arg3 in s6,
 * arg5 in s7); pin next. */
#ifdef NON_MATCHING
NON_MATCHING void func_801AFA1C(u8* arg0, u8 arg1, s16 arg2, s16 arg3, s32 arg4, s32 arg5, s32 arg6) {
    u8*  stack_10;
    u8   stack_18;
    u8   stack_20;
    u8   stack_28;
    s16  tmp0;
    s16  tmp1;
    s16  val0;
    s16  val1;
    s32  tmp2;
    s32  val2;
    s32  val3;
    s32  val4;
    u16  tmp3;
    u8** val5;
    u8   val6;
    u8   val7;
    u8   val8;

    val8     = (u8)arg5;
    val4     = 0;
    val0     = arg2;
    val1     = arg3;
    stack_10 = arg0;
    stack_18 = arg1;
    stack_20 = (u8)arg4;
    stack_28 = (u8)arg6;
    if (val8 != 0) {
        val7 = stack_28;
        val3 = val8 & BYTE_MASK;
        val6 = val8;
        do {
            val2 = val4 & HALF_MASK;
            if (stack_10[val2] != 0) {
                val5 = &g_GfxPrimCursor;
                val5 = (u8**)g_GfxPrimCursor;
                SetTile((TILE*)val5);
                FIELD(u8, val5, 0x5u)  = 0;
                FIELD(u8, val5, 0x6u)  = 0;
                FIELD(s16, val5, 0x8u) = (s16)(val0 + 4);
                FIELD(s16, val5, 0xCu) = 3;
                FIELD(u8, val5, 0x4u)  = 0x80;
                FIELD(u16, val5, 0xAu) = (u16)(val1 + (((s32)(val7 * val2) / val3) + 3));
                FIELD(u16, val5, 0xEu) =
                    (u16)((val1 + (((s32)(val7 * (val2 + 1)) / val3) + 3)) - FIELD(u16, val5, 0xAu));
                GFX_AddPrim(1U, sizeof(TILE));
            }
            val4 += 1;
        } while ((u32)(val4 & HALF_MASK) < val6);
    }
    val5 = &g_GfxPrimCursor;
    val5 = (u8**)g_GfxPrimCursor;
    SetPolyFT4((POLY_FT4*)val5);
    tmp2                    = val8 & BYTE_MASK;
    FIELD(u8, val5, 0x14u)  = 0x60;
    FIELD(u8, val5, 0x24u)  = 0x60;
    FIELD(s16, val5, 0x8u)  = val0;
    FIELD(s16, val5, 0x18u) = val0;
    FIELD(s16, val5, 0xCu)  = 0x58;
    FIELD(u8, val5, 0x1Cu)  = 0x58;
    tmp0                    = val0 + 8;
    FIELD(s16, val5, 0x10u) = tmp0;
    FIELD(s16, val5, 0x20u) = tmp0;
    FIELD(u8, val5, 0xDu)   = 0x98;
    FIELD(u8, val5, 0x15u)  = 0x98;
    FIELD(u8, val5, 0x1Du)  = 0x9F;
    FIELD(u8, val5, 0x25u)  = 0x9F;
    tmp3                    = val1 + ((((s32)((stack_28 * stack_18 * 2) + tmp2) / (s32)(tmp2 * 2)) & BYTE_MASK) + 3);
    FIELD(u16, val5, 0xAu)  = tmp3;
    FIELD(u16, val5, 0x12u) = tmp3;
    tmp1                    = tmp3 + ((s32)(stack_20 * stack_28) / tmp2);
    FIELD(s16, val5, 0x1Au) = tmp1;
    FIELD(s16, val5, 0x22u) = tmp1;
    FIELD(u16, val5, 0x16u) = GetTPage(0, 0, 832, 256);
    FIELD(u16, val5, 0xEu)  = GetClut(176, STAGE_PALETTE_Y + 1);
    FIELD(u8, val5, 0x4u)   = 0x80;
    FIELD(u8, val5, 0x5u)   = 0x80;
    FIELD(u8, val5, 0x6u)   = 0x80;
    GFX_AddPrim(1U, sizeof(POLY_FT4));
}
#else
INCLUDE_ASM(func_801AFA1C);
#endif

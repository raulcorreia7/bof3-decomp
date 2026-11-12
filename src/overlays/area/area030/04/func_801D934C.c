#include "area030_04.h"

#ifdef NON_MATCHING
NON_MATCHING void func_801D934C(s32 x, s32 y, s32 width, s32 height) {
    s32  stack_10;
    s32  stack_18;
    s32  stack_20;
    s8   val0;
    u16  tmp0;
    u16  val1;
    u16  val2;
    u16  val3;
    u16  val4;
    u16  val5;
    u16  val6;
    u32  val7;
    u8** val8;

    val4     = x;
    val3     = y;
    val6     = width;
    stack_10 = (s32)height;
    val2     = ((u16*)&D_80033A08)[(((u32)((*(s8*)&g_WindowStyle) << 6)) | 0x20) >> 1];
    val0     = (val2 & 0x1F) * 8;
    val2 &= HALF_MASK;
    val7 = val2 >> 2;
    val7 &= 0xF8;
    val2 = (u16)(val2 >> 7);
    val2 &= 0xF8;
    Fishing_SetDrawMode(6, 2);
    val8 = &g_GfxPrimCursor;
    val8 = (u8**)g_GfxPrimCursor;
    SetPolyF4((POLY_F4*)val8);
    stack_18                = val4 + 2;
    val5                    = val4 + val6;
    val1                    = val3 + 2;
    FIELD(u16, val8, 0x8u)  = (u16)stack_18;
    stack_20                = val5 - 2;
    FIELD(u16, val8, 0x10u) = val4;
    FIELD(u16, val8, 0x14u) = val5;
    FIELD(u16, val8, 0xAu)  = val3;
    FIELD(u16, val8, 0xEu)  = val3;
    FIELD(u16, val8, 0x12u) = val1;
    FIELD(u16, val8, 0x16u) = val1;
    FIELD(s8, val8, 0x4u)   = val0;
    FIELD(s8, val8, 0x5u)   = (s8)val7;
    FIELD(s8, val8, 0x6u)   = (s8)val2;
    FIELD(u16, val8, 0xCu)  = (u16)stack_20;
    SetSemiTrans(val8, 1);
    GFX_AddPrim(2U, sizeof(POLY_F4));
    val8 = &g_GfxPrimCursor;
    val8 = (u8**)g_GfxPrimCursor;
    SetTile((TILE*)val8);
    FIELD(u16, val8, 0x8u) = val4;
    FIELD(u16, val8, 0xAu) = val1;
    FIELD(u16, val8, 0xCu) = val6;
    FIELD(s8, val8, 0x4u)  = val0;
    FIELD(s8, val8, 0x5u)  = (s8)val7;
    FIELD(s8, val8, 0x6u)  = (s8)val2;
    FIELD(u16, val8, 0xEu) = (u16)(stack_10 - 4);
    SetSemiTrans(val8, 1);
    GFX_AddPrim(2U, sizeof(TILE));
    val8 = &g_GfxPrimCursor;
    val8 = (u8**)g_GfxPrimCursor;
    SetPolyF4((POLY_F4*)val8);
    FIELD(u16, val8, 0x8u)  = val4;
    FIELD(u16, val8, 0xCu)  = val5;
    FIELD(u16, val8, 0x10u) = (u16)stack_18;
    FIELD(u16, val8, 0x14u) = (u16)stack_20;
    val3 += stack_10;
    tmp0                    = val3 - 2;
    FIELD(u16, val8, 0xAu)  = tmp0;
    FIELD(u16, val8, 0xEu)  = tmp0;
    FIELD(u16, val8, 0x12u) = val3;
    FIELD(u16, val8, 0x16u) = val3;
    FIELD(s8, val8, 0x4u)   = val0;
    FIELD(s8, val8, 0x5u)   = (s8)val7;
    FIELD(s8, val8, 0x6u)   = (s8)val2;
    SetSemiTrans(val8, 1);
    GFX_AddPrim(2U, sizeof(POLY_F4));
}
#else
INCLUDE_ASM(func_801D934C);
#endif

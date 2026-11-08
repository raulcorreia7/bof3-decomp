#include "start_08.h"

/* nonmatching unmeasured: tried the first draft cleaned to compiling C; best score 65.42%. resume: a lever or header
 * fix that closes the first mismatch. */
#ifdef NON_MATCHING
NON_MATCHING void Menu_DrawHeaderBar(s32 x, s32 y, s32 width, s32 height, u8 window_style) {
    s32 stack_18;
    u8  early;
    s32 stack_20;
    s32 stack_28;
    s32 stack_30;
    u16 stack_38;
    s32 stack_40;
    s32 stack_48;
    s32 tmp0;
    s32 val0;
    s32 val1;
    s8  tmp1;
    u16 tmp2;
    u16 tmp3;
    u16 tmp4;
    u16 tmp5;
    u16 tmp6;
    u16 val2;
    u16 val3;
    u16 val4;
    u16 val5;
    u16 val6;
    u8* val7;
    u8  tmp7;
    u8  val8;

    val7                   = g_GfxPrimCursor;
    val8                   = window_style;
    early                  = window_style;
    stack_18               = x;
    stack_20               = y;
    stack_28               = width;
    stack_30               = height;
    g_GfxPrimCursor        = val7 + 8;
    FIELD(s16, val7, 0x2u) = 0xF0;
    *(s16*)(val7)          = 0;
    FIELD(s16, val7, 0x4u) = 0x10;
    FIELD(s16, val7, 0x6u) = 0x10;
    if (GetGraphType() != 1) {
        GetGraphType();
    }
    val3 = (u16)stack_18;
    val6 = (u16)stack_20;
    SetDrawMode((DR_MODE*)g_GfxPrimCursor, 0, 1, 0xF, (RECT*)val7);
    GFX_AddPrim(1U, sizeof(DR_MODE));
    val7 = g_GfxPrimCursor;
    SetPolyFT4((POLY_FT4*)val7);
    SetSemiTrans(val7, 1);
    val1                    = (val8 << 5) + 0x10;
    FIELD(u16, val7, 0x8u)  = val3;
    FIELD(u16, val7, 0xAu)  = val6;
    FIELD(u16, val7, 0x12u) = val6;
    FIELD(u16, val7, 0x18u) = val3;
    val2                    = stack_18 + 2;
    FIELD(u16, val7, 0x10u) = val2;
    val0                    = 0xAC;
    FIELD(u16, val7, 0x20u) = val2;
    FIELD(s8, val7, 0xCu)   = 0;
    FIELD(u8, val7, 0xDu)   = 0U;
    FIELD(u8, val7, 0x15u)  = 0U;
    FIELD(s8, val7, 0x1Cu)  = 0;
    FIELD(s16, val7, 0x4u)  = 0xAC;
    FIELD(s8, val7, 0x5u)   = 0xAC;
    FIELD(s16, val7, 0x6u)  = 0xAC;
    tmp7                    = stack_30 + 1;
    val4                    = stack_20 + tmp7;
    val8                    = tmp7;
    FIELD(u16, val7, 0x1Au) = val4;
    FIELD(u16, val7, 0x22u) = val4;
    FIELD(s8, val7, 0x14u)  = 2;
    FIELD(u8, val7, 0x1Du)  = val8;
    FIELD(s8, val7, 0x24u)  = 2;
    FIELD(u8, val7, 0x25u)  = val8;
    FIELD(u16, val7, 0xAu)  = (u16)(FIELD(u16, val7, 0xAu) + 2);
    FIELD(u16, val7, 0x1Au) = (u16)(FIELD(u16, val7, 0x1Au) - 3);
    FIELD(u8, val7, 0xDu)   = (u8)(FIELD(u8, val7, 0xDu) + 2);
    FIELD(u8, val7, 0x1Du)  = (u8)(FIELD(u8, val7, 0x1Du) - 3);
    FIELD(u16, val7, 0xEu)  = GetClut(val1, 481);
    stack_40                = stack_28 + 1;
    val3                    = (u16)stack_40;
    if (GetGraphType() != 1) {
        GetGraphType();
    }
    FIELD(s16, val7, 0x16u) = 0xF;
    GFX_AddPrim(1U, sizeof(POLY_FT4));
    val3     = (u16)((s32)((val3 & HALF_MASK) - 4) >> 1);
    val7     = g_GfxPrimCursor;
    stack_48 = (stack_28 - 3) & 1;
    SetPolyFT4((POLY_FT4*)val7);
    SetSemiTrans(val7, 1);
    tmp3                    = val3 + val2;
    val5                    = val3;
    FIELD(u16, val7, 0x8u)  = val2;
    FIELD(u16, val7, 0xAu)  = val6;
    FIELD(u16, val7, 0x10u) = tmp3;
    FIELD(u16, val7, 0x12u) = val6;
    FIELD(u16, val7, 0x18u) = val2;
    FIELD(u16, val7, 0x1Au) = val4;
    FIELD(u16, val7, 0x20u) = tmp3;
    FIELD(u16, val7, 0x22u) = val4;
    FIELD(s8, val7, 0xCu)   = 0;
    FIELD(u8, val7, 0xDu)   = 0U;
    FIELD(s8, val7, 0x14u)  = (s8)val5;
    FIELD(u8, val7, 0x15u)  = 0U;
    FIELD(s8, val7, 0x1Cu)  = 0;
    FIELD(u8, val7, 0x1Du)  = val8;
    FIELD(s8, val7, 0x24u)  = (s8)val5;
    FIELD(u8, val7, 0x25u)  = val8;
    FIELD(s16, val7, 0x4u)  = 0xAC;
    FIELD(s8, val7, 0x5u)   = 0xAC;
    FIELD(s16, val7, 0x6u)  = 0xAC;
    FIELD(u16, val7, 0xEu)  = GetClut(val1, 481);
    stack_38                = (u16)stack_48;
    if (GetGraphType() != 1) {
        GetGraphType();
    }
    FIELD(s16, val7, 0x16u) = 0xF;
    GFX_AddPrim(1U, sizeof(POLY_FT4));
    val7 = g_GfxPrimCursor;
    SetPolyFT4((POLY_FT4*)val7);
    SetSemiTrans(val7, 1);
    FIELD(u16, val7, 0xAu)  = val6;
    tmp0                    = stack_18 + val3;
    tmp2                    = tmp0 + 2;
    FIELD(u16, val7, 0x8u)  = tmp2;
    tmp5                    = tmp0 + (val3 + stack_48 + 2);
    FIELD(u16, val7, 0x10u) = tmp5;
    FIELD(u16, val7, 0x12u) = val6;
    FIELD(u16, val7, 0x18u) = tmp2;
    FIELD(u16, val7, 0x1Au) = val4;
    FIELD(u16, val7, 0x20u) = tmp5;
    FIELD(u16, val7, 0x22u) = val4;
    FIELD(s8, val7, 0xCu)   = 0;
    FIELD(u8, val7, 0xDu)   = 0U;
    tmp1                    = val5 + stack_38;
    FIELD(s8, val7, 0x14u)  = tmp1;
    FIELD(u8, val7, 0x15u)  = 0U;
    FIELD(s8, val7, 0x1Cu)  = 0;
    FIELD(u8, val7, 0x1Du)  = val8;
    FIELD(s8, val7, 0x24u)  = tmp1;
    FIELD(u8, val7, 0x25u)  = val8;
    FIELD(s16, val7, 0x4u)  = 0xAC;
    FIELD(s8, val7, 0x5u)   = 0xAC;
    FIELD(s16, val7, 0x6u)  = 0xAC;
    FIELD(u16, val7, 0xEu)  = GetClut(val1, 481);
    if (GetGraphType() != 1) {
        GetGraphType();
    }
    FIELD(s16, val7, 0x16u) = 0xF;
    GFX_AddPrim(1U, sizeof(POLY_FT4));
    val7 = g_GfxPrimCursor;
    SetPolyFT4((POLY_FT4*)val7);
    SetSemiTrans(val7, 1);
    tmp4                    = stack_18 + stack_40;
    FIELD(u16, val7, 0x1Au) = val4;
    tmp6                    = tmp4 - 2;
    FIELD(u8, val7, 0x1Du)  = val8;
    FIELD(u16, val7, 0x10u) = tmp4;
    FIELD(u16, val7, 0x12u) = val6;
    FIELD(u16, val7, 0x20u) = tmp4;
    FIELD(u16, val7, 0x8u)  = tmp6;
    FIELD(u16, val7, 0x18u) = tmp6;
    FIELD(u16, val7, 0x22u) = val4;
    FIELD(u16, val7, 0xAu)  = val6;
    FIELD(s8, val7, 0xCu)   = 0;
    FIELD(u8, val7, 0xDu)   = 0U;
    FIELD(s8, val7, 0x14u)  = 2;
    FIELD(u8, val7, 0x15u)  = 0U;
    FIELD(s8, val7, 0x1Cu)  = 0;
    FIELD(s8, val7, 0x24u)  = 2;
    FIELD(u8, val7, 0x25u)  = val8;
    FIELD(s16, val7, 0x4u)  = 0xAC;
    FIELD(s8, val7, 0x5u)   = 0xAC;
    FIELD(s16, val7, 0x6u)  = 0xAC;
    FIELD(u16, val7, 0x12u) = (u16)(FIELD(u16, val7, 0x12u) + 2);
    FIELD(u16, val7, 0x22u) = (u16)(FIELD(u16, val7, 0x22u) - 3);
    FIELD(u16, val7, 0x1Au) = (u16)(FIELD(u16, val7, 0x1Au) - 1);
    FIELD(u8, val7, 0x15u)  = (u8)(FIELD(u8, val7, 0x15u) + 2);
    FIELD(u8, val7, 0x1Du)  = (u8)(FIELD(u8, val7, 0x1Du) - 1);
    FIELD(u8, val7, 0x25u)  = (u8)(FIELD(u8, val7, 0x25u) - 3);
    FIELD(u16, val7, 0xEu)  = GetClut(val1, 481);
    if (GetGraphType() != 1) {
        GetGraphType();
    }
    FIELD(s16, val7, 0x16u) = 0xF;
    GFX_AddPrim(1U, sizeof(POLY_FT4));
    val7                   = g_GfxPrimCursor;
    g_GfxPrimCursor        = val7 + 8;
    *(s16*)(val7)          = 0;
    FIELD(s16, val7, 0x2u) = 0;
    FIELD(s16, val7, 0x4u) = 0x100;
    FIELD(s16, val7, 0x6u) = 0x100;
    if (GetGraphType() != 1) {
        GetGraphType();
    }
    SetDrawMode((DR_MODE*)g_GfxPrimCursor, 0, 1, 0xF, (RECT*)val7);
    GFX_AddPrim(1U, sizeof(DR_MODE));
    func_801AEBA0((s16)val2, (s16)(stack_20 + 2), (s16)(stack_28 - 4), (s16)(stack_30 - 4), 0);
}
#else
INCLUDE_ASM(Menu_DrawHeaderBar);
#endif

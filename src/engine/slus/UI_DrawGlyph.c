#include "engine/slus/slus.h"

#ifdef NON_MATCHING
NON_MATCHING void UI_DrawGlyph(s32 color, u8* text) {
    /* 73.14%; regalloc: the saved arguments are reversed. Pinning the text pointer to s1
     * (work/exe/slus_004_22/80151E24/best.c) reaches 77.99%, then the draw-mode constant is hoisted
     * before the s1 spill. resume: a shape that keeps retail's copy order without the pin. */
    u8* val0;
    s32 val1;
    s32 val2;

    val0 = text;
    val1 = color;
    SetDrawMode((DR_MODE*)g_GfxPrimCursor, 0, 0, GetTPage(0, 1, 960, 1) & HALF_MASK, NULL);
    GFX_AddPrim(1U, 0xCU);
    val1 &= 0xF;
    FIELD(u16, g_GfxPrimCursor, 0xEu) = GetClut(val1 * 16, 480);
    val1                              = 8;
    if (D_801490BC.cue_counter < 9) {
        val2 = 0xC;
    } else {
        val1 = 7;
        val2 = 0xB;
    }
    if (*val0 != STRING_SPACE) {
        FIELD(u16, g_GfxPrimCursor, 0x16u) = GetTPage(0, 1, 960, 0);
        FIELD(s8, g_GfxPrimCursor, 0xCu)   = (s8)(((*val0 - '0') % 31) * 8);
        FIELD(s8, g_GfxPrimCursor, 0xDu)   = (s8)((((*val0 - '0') / 31) * 0xC) + 0x48);
        FIELD(s8, g_GfxPrimCursor, 0x14u)  = (s8)(val1 + (((*val0 - '0') % 31) * 8));
        FIELD(s8, g_GfxPrimCursor, 0x15u)  = (s8)((((*val0 - '0') / 31) * 0xC) + 0x48);
        FIELD(s8, g_GfxPrimCursor, 0x1Cu)  = (s8)(((*val0 - '0') % 31) * 8);
        FIELD(s8, g_GfxPrimCursor, 0x1Du) =
            (s8)((((*val0 - '0') / 31) * 0xC) + 0x48 + (val2 - g_TextRowOffsets[D_801490B8[0]]));
        FIELD(s8, g_GfxPrimCursor, 0x24u) = (s8)(val1 + (((*val0 - '0') % 31) * 8));
        FIELD(s8, g_GfxPrimCursor, 0x25u) =
            (s8)((((*val0 - '0') / 31) * 0xC) + 0x48 + (val2 - g_TextRowOffsets[D_801490B8[0]]));
        FIELD(s8, g_GfxPrimCursor, 0x4u)   = 0x80;
        FIELD(s8, g_GfxPrimCursor, 0x5u)   = 0x80;
        FIELD(s8, g_GfxPrimCursor, 0x6u)   = 0x80;
        FIELD(u16, g_GfxPrimCursor, 0x8u)  = (u16)D_801490BC.text_x;
        FIELD(u16, g_GfxPrimCursor, 0xAu)  = (u16)D_801490BC.text_y;
        FIELD(s16, g_GfxPrimCursor, 0x10u) = (s16)((u16)D_801490BC.cue_counter + (D_801490BC.text_x + 8));
        FIELD(u16, g_GfxPrimCursor, 0x12u) = (u16)D_801490BC.text_y;
        FIELD(u16, g_GfxPrimCursor, 0x18u) = (u16)D_801490BC.text_x;
        FIELD(s16, g_GfxPrimCursor, 0x1Au) =
            (s16)(D_801490BC.text_y + (((u16)D_801490BC.cue_counter + 0xC) -
                                       ((s32)(((((s32)((u16)D_801490BC.cue_counter << 0x10) >> 0xC) + 0xC0) / 12) *
                                              g_TextRowOffsets[D_801490B8[0]]) >>
                                        4)));
        FIELD(s16, g_GfxPrimCursor, 0x20u) = (s16)((u16)D_801490BC.cue_counter + (D_801490BC.text_x + 8));
        FIELD(s16, g_GfxPrimCursor, 0x22u) =
            (s16)(D_801490BC.text_y + (((u16)D_801490BC.cue_counter + 0xC) -
                                       ((s32)(((((s32)((u16)D_801490BC.cue_counter << 0x10) >> 0xC) + 0xC0) / 12) *
                                              g_TextRowOffsets[D_801490B8[0]]) >>
                                        4)));
        SetPolyFT4((POLY_FT4*)g_GfxPrimCursor);
        PSX_SET_SEMI_TRANSPARENT(g_GfxPrimCursor);
        GFX_AddPrim(1U, 0x28U);
    }
    D_801490BC.text_x += (u16)D_801490BC.cue_counter;
}
#else
INCLUDE_ASM(UI_DrawGlyph);
#endif

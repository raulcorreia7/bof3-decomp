#include "game_01.h"

/* Each record supplies the glyph's UV origin, size, and CLUT Y. */
// clang-format off
static const WinGlyphGeometry D_801D1C6C[WIN_GLYPH_GEOMETRY_COUNT] = {
    {84, 60, 10, 10, 480},
    {96, 60, 12, 10, 480},
    {0, 0, 240, 160, 485},
    {0, 160, 48, 48, 485},
    {0, 0, 224, 128, 484},
    {0, 128, 96, 128, 484},
    {0, 208, 96, 16, 485},
    {0, 0, 224, 16, 486},
    {0, 16, 160, 16, 486},
    {0, 48, 144, 16, 486},
    {0, 0, 128, 80, 494},
    {0, 0, 256, 192, 487},
    {0, 0, 256, 192, 488},
    {0, 0, 256, 192, 489},
    {0, 0, 256, 192, 490},
    {0, 0, 224, 128, 491},
    {0, 128, 96, 128, 491},
    {0, 0, 240, 160, 491},
    {0, 160, 48, 48, 491},
    {0, 32, 160, 16, 486},
};
// clang-format on

/* The handler opens the selection-specific EXE effect for the current
 * selection.
 */
/* func_801D1134 */
MATCH void SND_StartSelectionEffect(void) { /* func_801D1134 */
    u8 selection;

    selection = g_SndBgmId;

    if (selection != 0xFFu) {
        u32 offset = selection << 2;

        SND_StartDecrescendo(g_SelectionCues[offset], g_SelectionCues[offset + 1u], 100, 0x10);
    }
}

/* The handler closes the current selection-specific EXE effect and clears
 * the active selection byte.
 */
/* func_801D1184 */
MATCH void SND_StopSelectionEffect(void) { /* func_801D1184 */
    u8* selection_ptr = &g_SndBgmId;
    u8  selection     = *selection_ptr;

    if (selection != 0xFFu) {
        u32 offset = selection << 2;

        SND_StopSequence(g_SelectionCues[offset], g_SelectionCues[offset + 1u]);
        *selection_ptr = 0xFFu;
    }
}

/* The handler clears the prompt gate after the EXE reaches idle selection
 * state, then draws the active frontend prompt and selection marker.
 */
/* func_801D11E4 */
MATCH void UI_DrawChoicePrompt(void) { /* func_801D11E4 */
    if (g_GameStateIndex == GAME_REQUEST_AREA_CHANGE && g_GameEntryState == 2u && g_UiWindowEffectBusy == 0u) {
        LOBU(g_UiPopupRequest) = 0u;
    }

    if (g_AreaDrawFlags != 0u && LOBU(g_UiPopupRequest) != 0u) {
        SetDrawMode((DR_MODE*)g_GfxPrimCursor, 0, 0, getTPage(1, 0, 832, 256), 0);
        GFX_AddPrim(2, 12);
        GFX_BuildGlyphPrimitive(192, 4, 10, 2, 0);
    }
}

/* The handler draws both New Game/Load prompt panels, their labels, and the
 * selection marker. When the popup is open, it pulses the active marker.
 */
/* func_801D12CC */
MATCH void UI_DrawChoicePanels(u8 selected, u8 alpha) { /* func_801D12CC */
    u8* primitive;
    s32 tpage;
    s32 pulse;
    s32 pulse_counter;

    tpage = getTPage(0, 1, 960, 0);
    GFX_SET_DRAW_MODE(tpage);
    GFX_AddPrim(1, 12);
    primitive = GFX_BuildGlyphPrimitive(262, 130, 1, 1, selected);
    GFX_SetPrimitiveAlpha(primitive, alpha);

    tpage = getTPage(1, 1, 832, 256);
    GFX_SET_DRAW_MODE(tpage);
    GFX_AddPrim(2, 12);
    primitive = GFX_BuildGlyphPrimitive(12, 200, 8, 2, selected);
    GFX_SetPrimitiveAlpha(primitive, alpha);

    tpage = getTPage(1, 1, 832, 256);
    GFX_SET_DRAW_MODE(tpage);
    GFX_AddPrim(2, 12);
    primitive = GFX_BuildGlyphPrimitive(12, 212, 19, 2, selected);
    GFX_SetPrimitiveAlpha(primitive, alpha);
    primitive = GFX_BuildGlyphPrimitive(172, 212, 9, 2, selected);
    GFX_SetPrimitiveAlpha(primitive, alpha);

    if ((g_UiPopupRequest & WIN_POPUP_PENDING_MASK) == WIN_POPUP_PENDING_OPEN) {
        primitive     = GFX_BuildGlyphPrimitive(48, 184, 7, 2, 0);
        pulse_counter = D_80143C2A + 1u;
        D_80143C2A    = pulse_counter;
        pulse = (pulse_counter & 0x20u) == 0u ? ((pulse_counter & 0x1Fu) << 2) : -128 - ((pulse_counter & 0x1Fu) << 2);
        primitive[4] = pulse;
        primitive[5] = pulse;
        primitive[6] = pulse;
    } else {
        D_80143C2A = 0u;
    }
}

/* The handler draws two paired frontend label groups at the requested
 * position. The first expanded pair is optional; both groups use the same
 * selection and alpha controls.
 */
/* func_801D150C */
MATCH void UI_DrawLabelPair(s16 x, s16 y, u8 selected, u8 alpha) { /* func_801D150C */
    u8* primitive;
    s32 tpage;

    if (selected != 0u) {
        tpage = getTPage(1, 2, 576, 256);
        GFX_SET_DRAW_MODE(tpage);
        GFX_AddPrim(2, 12);
        primitive = GFX_BuildGlyphPrimitive(x, y, 15, 2, 1);
        GFX_SetPrimitiveAlpha(primitive, alpha);
        primitive = GFX_BuildGlyphPrimitive((s16)(x + 224), y, 16, 2, 1);
        GFX_SetPrimitiveAlpha(primitive, alpha);
    }

    tpage = getTPage(1, 1, 576, 256);
    GFX_SET_DRAW_MODE(tpage);
    GFX_AddPrim(2, 12);
    primitive = GFX_BuildGlyphPrimitive(x, y, 4, 2, selected);
    GFX_SetPrimitiveAlpha(primitive, alpha);
    primitive = GFX_BuildGlyphPrimitive((s16)(x + 224), y, 5, 2, selected);
    GFX_SetPrimitiveAlpha(primitive, alpha);
}

/* The handler draws a paired frontend label group at the requested position
 * and applies the supplied selection and alpha controls to both primitives.
 */
/* func_801D16DC */
MATCH void UI_DrawIconPair(s16 x, s16 y, u8 selected, u8 alpha) { /* func_801D16DC */
    u8* primitive;
    s32 tpage;

    tpage = getTPage(1, 1, 704, 256);
    GFX_SET_DRAW_MODE(tpage);
    GFX_AddPrim(2, 12);
    primitive = GFX_BuildGlyphPrimitive(x, y, 2, 2, selected);
    GFX_SetPrimitiveAlpha(primitive, alpha);
    primitive = GFX_BuildGlyphPrimitive((s16)(x + 240), (s16)(y + 112), 3, 2, selected);
    GFX_SetPrimitiveAlpha(primitive, alpha);
}

/* The table has five u16 fields per 10-byte row. Keep each symbol-relative
 * base separate so the loads retain the retail code shape. */

/* func_801D17D8 */
MATCH u8* GFX_BuildGlyphPrimitive(s32 x, s32 y, s32 glyph, s32 palette, u8 flags) { /* func_801D17D8 */
    u8*   primitive;
    SPRT* sprite;
    u32   geom;

    primitive = (u8*)g_GfxPrimCursor;
    sprite    = (SPRT*)primitive;
    SetSprt(sprite);
    SetSemiTrans(primitive, flags);

    setRGB0(sprite, 128u, 128u, 128u);
    geom         = (u8)glyph * (WIN_GEOMETRY_STRIDE * 2u);
    sprite->x0   = (s16)x;
    sprite->y0   = (s16)y;
    sprite->u0   = (u8) * (u16*)(((u8*)D_801D1C6C + geom));
    sprite->v0   = (u8) * (u16*)(((u8*)&D_801D1C6E + geom));
    sprite->w    = *(u16*)(((u8*)&D_801D1C70 + geom));
    sprite->h    = *(u16*)(((u8*)&D_801D1C72 + geom));
    sprite->clut = (u16)(*(u16*)(((u8*)&D_801D1C74 + geom)) << 6);
    GFX_AddPrim((u8)palette, 20);
    return primitive;
}

/* The handler writes one alpha value to the three color channels of a
 * frontend primitive.
 */
/* func_801D18E8 */
MATCH void GFX_SetPrimitiveAlpha(u8* primitive, u8 alpha) { /* func_801D18E8 */
    primitive[4] = alpha;
    primitive[5] = alpha;
    primitive[6] = alpha;
}

/* func_801D18F8 */
MATCH void UI_UpdateBannerFade(void) { /* func_801D18F8 */
    volatile GameUIBannerState* state;
    volatile u16*               alpha;
    volatile u8*                phase_addr;
    s32                         i;
    s32                         x;
    s32                         marker;
    s32                         flags;
    s32                         a;
    s32                         sc;
    s32                         one;
    u8                          phase;
    u8*                         primitive;

    /* Anchor the banner state on the fade-phase byte: the original derives the
     * scroll base (-15) and alpha cell (-13) from &g_UiTitleFadePhase. */
    phase_addr = &g_UiTitleFadePhase;
    if (*phase_addr == 0) {
        return;
    }
    /* FAKE: the counter clear is the only statement of the block that follows
     * the guard, so it stays that block's first insn (retail's `beqz` delay
     * slot, `+0x34 move s1,zero`) without lengthening i's live range across
     * the rest of the pre-loop statements the way an unlocked early `i = 0`
     * does (the swap the RESIDUAL note records). Candidate's predecessor note:
     * "a source shape that keeps i's live range at 98 insns while making
     * `i = 0` the first insn after the branch". */
    ORDER_LOCK(i = 0);
    state                 = (GameUIBannerState*)((phase_addr - 15));
    /* FAKE: retail materialises the loop's constant 1 between the state and
     * alpha computations (`+0x3c addiu s5,zero,1` between `+0x38 addiu
     * s0,v1,-15` and `+0x40 addiu s4,v1,-13`), not at the loop-invariant hoist
     * site; carrying it in a named local the two loop compares read puts the
     * `li` at this statement while the value still lives in a callee-saved
     * register across the loop's calls. */
    one                   = 1;
    alpha                 = &state->alpha;
    sc                    = g_UiTitleBannerScroll + 2;
    x                     = 320 - sc;
    g_UiTitleBannerScroll = sc;
    marker                = 320;

    for (; i < 4; x += 255, i++, marker += 128) {
        if (i < (s16)state->scroll / 640) {
            continue;
        }

        /* Read the dispatch phase through a non-volatile view so cc1 does not emit
         * an andi 0xFF zero-extension before the == 1 / == 3 compares. */
        phase = LOBU(state->phase);
        if (phase == one) {
            a            = state->alpha + 1;
            state->alpha = a;
            if ((s16)a >= 128) {
                a                  = 128;
                state->alpha       = a;
                a                  = 2;
                LOBU(state->phase) = a;
            }
        } else if (phase == 3) {
            a            = state->alpha - 1;
            state->alpha = a;
            if ((s16)a <= 0) {
                state->alpha       = 0;
                LOBU(state->phase) = 0;
            }
        } else {
            a            = 128;
            state->alpha = a;
        }

        if (g_UiTitleFadePhase == 0) {
            continue;
        }

        flags = GetGraphType() == one ? ((marker & 0x3FF) >> 6) | 0x200
                : GetGraphType() == 2 ? ((marker & 0x3FF) >> 6) | 0x200
                                      : ((marker & 0x3FF) >> 6) | 0x80;
        GFX_SET_DRAW_MODE(flags);

        GFX_AddPrim(2, 12);
        primitive    = GFX_BuildGlyphPrimitive((s16)x, 24, (u8)(i + 11), 2, 0);
        primitive[4] = *alpha;
        primitive[5] = *alpha;
        primitive[6] = *alpha;
    }
}

/* The handler advances the two frontend window fades. It promotes the fade
 * phase when both channels saturate and draws the visible menu/window layers.
 */
/* func_801D1B00 */
MATCH void UI_UpdateWindowFade(void) { /* func_801D1B00 */
    /* FAKE: volatile u8 alias emits ephemeral lbu reads. */
    u8* phase;
    u8  p;
    /* FAKE: pin holds fade flags in s0 s1. */
    u8  primary_active;
    u8  secondary_active;
    /* FAKE: pin keeps increment in one register. */
    s32 alpha;

    primary_active   = 1;
    secondary_active = 1;
    phase            = (u8*)&g_UiTitleChoicePhase;

    p = *phase;
    if (p == 1u) {
        alpha                 = g_UiTitlePrimaryAlpha + 4u;
        g_UiTitlePrimaryAlpha = (u16)alpha;
        if ((s16)alpha >= 128) {
            g_UiTitlePrimaryAlpha = 128u;
            primary_active        = 0;
        }

        alpha                   = g_UiTitleSecondaryAlpha + 2u;
        g_UiTitleSecondaryAlpha = (u16)alpha;
        if ((s16)alpha >= 128) {
            g_UiTitleSecondaryAlpha = 128u;
            secondary_active        = 0;
        }

        if (primary_active == 0u && secondary_active == 0u) {
            *phase = 2u;
        }
    } else if (p == 2u) {
        primary_active          = 0;
        secondary_active        = 0;
        g_UiTitlePrimaryAlpha   = 128u;
        g_UiTitleSecondaryAlpha = 128u;
    }

    if (g_UiTitleChoicePhase != 0u) {
        UI_DrawChoicePanels(secondary_active, LOBU(g_UiTitleSecondaryAlpha));
        /* FAKE: second read addressed off the primary word so the secondary
         * address is not shared across the call. */
        UI_DrawIconPair(26, 24, secondary_active, FIELD(u8, &g_UiTitlePrimaryAlpha, 2));
        UI_DrawLabelPair(-6, 28, primary_active, LOBU(g_UiTitlePrimaryAlpha));
    }
}

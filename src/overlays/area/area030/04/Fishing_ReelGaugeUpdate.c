#include "area030_04.h"

/* func_801D2DC4 */
/* Reel gauge: moves the cursor toward the hooked fish's limit, then draws the gauge line, the
 * cursor row and the fish arrow. */
#ifdef NON_MATCHING
NON_MATCHING void Fishing_ReelGaugeUpdate(void) {
    LINE_F2* prim;
    void*    work;
    s16      origin_y;
    s16      screen_y;
    s16      cursor;
    s16      clamped;
    s16      line;
    s16      marker_y;
    s16      y_limit;
    s32      step;
    s32      span;
    s32      band;
    s8       flip;
    s8       limit;
    u8       timer;
    u8       reel_size;

    Fishing_SetDrawMode(0, 2);
    Fishing_DrawSprite(0x11, 2, 135, 180);
    work = g_Task;
    if (FIELD(s32, work, 0x10u) != 0) {
        FIELD(u8, work, 0x9u) = 0;
    } else {
        origin_y = FIELD(s16, work, 0x30u);
        limit    = (s8)g_Actors[g_FishingHookedFish].unk_0A;
        step     = g_FishingRodRow->reel_cursor_size * 4;
        if (((origin_y + step + 12) < limit) || (limit < ((origin_y - step) - 12))) {
            timer = FIELD(u8, work, 0x9u);
            if (timer >= 0xF) {
                if (limit < origin_y) {
                    FIELD(s32, work, 0x10u) = -1;
                } else if (origin_y < limit) {
                    FIELD(s32, work, 0x10u) = 1;
                }
            } else {
                FIELD(u8, work, 0x9u) = (u8)(timer + 1);
            }
        } else {
            FIELD(u8, work, 0x9u) = 0;
        }
    }
    work                    = g_Task;
    screen_y                = (s16)(FIELD(u16, work, 0x30u) + FIELD(s32, work, 0x10u));
    FIELD(s16, work, 0x30u) = screen_y;
    step                    = g_FishingRodRow->reel_cursor_size * 4;
    cursor                  = (s16)(step - 36);
    if (screen_y >= cursor) {
        cursor = (s16)(36 - step);
        if (screen_y <= cursor) {
            cursor = (s16)FIELD(u16, work, 0x30u);
        }
    }
    FIELD(s16, work, 0x30u) = cursor;
    prim                    = (LINE_F2*)g_GfxPrimCursor;
    SetLineF2(prim);
    prim->x0 = 185;
    prim->x1 = 185;
    prim->y0 = 201;
    prim->y1 = 213;
    setRGB0(prim, 128, 128, 128);
    GFX_AddPrim(GFX_LAYER_EFFECT_FRONT, sizeof(LINE_F2));

    work      = g_Task;
    reel_size = g_FishingRodRow->reel_cursor_size;
    span      = reel_size * 8;
    band      = span + 24;
    line      = (s16)((FIELD(u16, work, 0x30u) - (reel_size * 4)) + 173);
    marker_y  = (s16)(line + span + 24);
    y_limit   = (s16)((s8)g_Actors[g_FishingHookedFish].unk_0A + 185);
    if ((marker_y < y_limit) || (y_limit < line)) {
        Fishing_DrawReelCursor(line, 203, band & 0xF8, (FIELD(u8, work, 0xAu) & 7) * 2, 2, 1);
    } else {
        Fishing_DrawReelCursor(line, 203, band & 0xF8, (FIELD(u8, work, 0xAu) & 7) * 2, 2, 0);
    }
    if (g_Actors[g_FishingHookedFish].header.mode == 4) {
        prim = (LINE_F2*)g_GfxPrimCursor;
        SetLineF2(prim);
        prim->x0 = 136;
        prim->x1 = (s16)(((g_Actors[g_FishingHookedFish].ext.bounds.half_height * 96) / 256) + 136);
        prim->y0 = 211;
        prim->y1 = 211;
        setRGB0(prim, 128, 0, 0);
        GFX_AddPrim(GFX_LAYER_EFFECT_FRONT, sizeof(LINE_F2));

        flip = (s8)(g_Actors[g_FishingHookedFish].vy >= 0);
        if (y_limit < 144) {
            clamped = 144;
        } else if (y_limit < 229) {
            clamped = y_limit;
        } else {
            clamped = 228;
        }
        Fishing_DrawFishArrow(clamped, 203, flip, 2U);
        if ((D_80145E92[0] == 4) && (g_Actors[g_FishingHookedFish].unk_04 != 3) && ((marker_y < clamped) || (clamped < line)) && !(g_FrameCount & 0xF)) {
            SND_SEPlay(EMI_SE_ID(SND_BANK_AREA, 7));
        }
    }
}
#else
INCLUDE_ASM(Fishing_ReelGaugeUpdate);
#endif

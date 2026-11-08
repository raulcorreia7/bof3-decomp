#include "area030_04.h"

/* Steps the battle cursor row: it nudges the cursor up or down while the actor stands inside the row
 * band, then draws the cursor line and the row marker. */
/* nonmatching unmeasured: tried the retail loads the work pointer into a0 and the candidate into a1, and the
 * saved-register plan follows from it. resume: a source shape that keeps the work pointer in a0 after the panel call.
 */
/* func_801D2DC4 */
#ifdef NON_MATCHING
NON_MATCHING void Fishing_ReelGaugeUpdate(void) {
    s16    marker_y_now;
    s16    line;
    s16    origin_y;
    s16    gap;
    s16    row_limit;
    s16    origin_y_now;
    s16    cursor_limit;
    s16    marker_top;
    s16    marker_y;
    s16    line_y;
    s16    marker_clamp;
    s32    span;
    s32    step_bytes;
    s32    band;
    s32    step;
    s32    scroll;
    s8     limit;
    u8**   prim;
    u8     row_flags;
    u8     timer;
    Actor* work;
    void*  work_now;
    void*  work_row;

    func_801E0C80(0, 2);
    func_801E0DCC(0x11, 2, 135, 180);
    work = g_Task;
    if ((work->unk_10 == 0) && ((origin_y = work->unk_30, limit = *(&D_80146892 + (g_FishingHookedFish * 0x98)),
                                 step = g_FishingRodRow->byte_03 * 4, (((origin_y + step + 12) < limit) != 0)) ||
                                (limit < ((origin_y - step) - 12)))) {
        timer = work->unk_09;
        if (timer >= 0xFU) {
            if (limit < origin_y) {
                work->unk_10 = -1;
            } else if (origin_y < limit) {
                work->unk_10 = 1;
            }
        } else {
            work->unk_09 = (u8)(timer + 1);
        }
    } else {
        work->unk_09 = 0U;
    }
    work_row                    = g_Task;
    origin_y_now                = (u16)(FIELD(s16, work_row, 0x30u)) + FIELD(s32, work_row, 0x10u);
    FIELD(s16, work_row, 0x30u) = origin_y_now;
    step_bytes                  = g_FishingRodRow->byte_03 * 4;
    cursor_limit                = step_bytes - 36;
    if (origin_y_now >= cursor_limit) {
        gap          = 36 - step_bytes;
        cursor_limit = gap;
        if (gap >= origin_y_now) {
            cursor_limit = (s16)(u16)(FIELD(s16, work_row, 0x30u));
        }
    }
    prim                        = &g_GfxPrimCursor;
    prim                        = (u8**)g_GfxPrimCursor;
    FIELD(s16, work_row, 0x30u) = cursor_limit;
    SetLineF2((LINE_F2*)prim);
    FIELD(s16, prim, 0x8u) = 185;
    FIELD(s16, prim, 0xCu) = 185;
    FIELD(s16, prim, 0xAu) = 201;
    FIELD(s16, prim, 0xEu) = 213;
    FIELD(s8, prim, 0x4u)  = 0x80;
    FIELD(s8, prim, 0x5u)  = 0x80;
    FIELD(s8, prim, 0x6u)  = 0x80;
    GFX_AddPrim(2U, 0x10U);
    work_now     = g_Task;
    row_flags    = g_FishingRodRow->byte_03;
    span         = row_flags * 8;
    band         = span + 24;
    line         = ((u16)(FIELD(s16, work_now, 0x30u)) - (row_flags * 4)) + 173;
    marker_y_now = line + span + 24;
    marker_y     = marker_y_now;
    row_limit    = (s8) * (&D_80146892 + (g_FishingHookedFish * 0x98)) + 185;
    marker_top   = row_limit;
    line_y       = line;
    if ((marker_y_now < row_limit) || (row_limit < line)) {
        Fishing_DrawReelCursor(line, 203, band & 0xF8, (FIELD(u8, work_now, 0xAu) & 7) * 2, 2, 1);
    } else {
        Fishing_DrawReelCursor(line, 203, band & 0xF8, (FIELD(u8, work_now, 0xAu) & 7) * 2, 0, 0);
    }
    if (*(D_80146889 + (g_FishingHookedFish * 0x98)) == 4) {
        prim = &g_GfxPrimCursor;
        prim = (u8**)g_GfxPrimCursor;
        SetLineF2((LINE_F2*)prim);
        FIELD(s16, prim, 0x8u) = 136;
        scroll                 = *(&D_80146916 + (g_FishingHookedFish * 0x98)) * 96;
        if (scroll < 0) {
            scroll += 0xFF;
        }
        FIELD(s16, prim, 0xCu) = (s16)((scroll >> 8) + 136);
        FIELD(s16, prim, 0xAu) = 211;
        FIELD(s16, prim, 0xEu) = 211;
        FIELD(s8, prim, 0x4u)  = 0x80;
        FIELD(s8, prim, 0x5u)  = 0;
        FIELD(s8, prim, 0x6u)  = 0;
        GFX_AddPrim(2U, 0x10U);
        if (marker_top >= 144) {
            marker_clamp = marker_top;
            if (marker_top >= 229) {
                marker_clamp = 228;
            }
        } else {
            marker_clamp = 144;
        }
        prim = (u8**)marker_clamp;
        Fishing_DrawFishArrow((s16)prim, 203, (s8)((u32) ~*(&D_80146898 + (g_FishingHookedFish * 0x98)) >> 0x1F), 2U);
        if ((D_80145E92 == 4) && (*(&D_8014688C + (g_FishingHookedFish * 0x98)) != 3) &&
            ((marker_y < (s32)prim) || ((s32)prim < line_y)) && !(g_FrameCount & 0xF)) {
            SND_PlayCue(EMI_CUE_ID(2, 7));
        }
    }
}
#else
INCLUDE_ASM(Fishing_ReelGaugeUpdate);
#endif

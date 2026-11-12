#include "area030_04.h"

/* Slides the AREA030 fishing panel in: steps the slide counter at
 * work+0x09 down, draws the panel bars, the recorded or blank catch row keyed
 * by work+0x3E, the counter panel and the frame offset by that counter, then
 * the option mask, and advances the work state at work+0x01 once the counter
 * reaches zero. */
MATCH void func_801D4984(void) {
    s16 key;
    s32 mask;

    FISHING_STATE->step_timer_09--;
    Fishing_DrawCatchBar(-(FISHING_STATE->step_timer_09 * 80), FISHING_CATCH_BAR_Y);
    key = FISHING_STATE->bounce_3C.half.key_3E;
    if (g_FishingBestCatch[key] != 0) {
        Fishing_DrawCatchIcon(FISHING_STATE->step_timer_09 * FISHING_CATCH_ICON_STEP + FISHING_CATCH_ICON_X, FISHING_CATCH_ICON_Y, key);
        func_801E1004(FISHING_STATE->bounce_3C.half.key_3E & BYTE_MASK, g_FishingBestCatch[FISHING_STATE->bounce_3C.half.key_3E], FISHING_STATE->step_timer_09);
    } else {
        Fishing_DrawCatchIcon(FISHING_STATE->step_timer_09 * FISHING_CATCH_ICON_STEP + FISHING_CATCH_ICON_X, FISHING_CATCH_ICON_Y, GAME_NONE);
        func_801E1004(0xFF, 0, FISHING_STATE->step_timer_09);
    }
    Fishing_DrawRank(FISHING_CATCH_RANK_X, FISHING_STATE->step_timer_09 * FISHING_CATCH_ROW_STEP + FISHING_CATCH_RANK_Y);
    Fishing_DrawIconRow(8, FISHING_STATE->step_timer_09 * FISHING_CATCH_ROW_STEP + FISHING_CATCH_ROW_Y, 65535);
    Fishing_DrawWindowFrame(MENU_HEADER_X, MENU_HEADER_Y, MENU_HEADER_WIDTH, MENU_HEADER_HEIGHT, 0);
    mask = 0;
    if (D_80145E93[0] >= 3u) {
        mask = BIT(FISHING_STATE->cue_index_06) & BYTE_MASK;
    }
    func_801D7C10(FISHING_SHOP_COLUMNS_X, FISHING_SHOP_COLUMNS_Y, mask);
    if (FISHING_STATE->step_timer_09 == 0) {
        FISHING_STATE->handler_index_01++;
    }
}

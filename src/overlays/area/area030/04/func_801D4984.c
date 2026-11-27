#include "area030_04.h"

/* Slides the AREA030 fishing panel in: steps the slide counter at
 * work+0x09 down, draws the panel bars, the recorded or blank catch row keyed
 * by work+0x3E, the counter panel and the frame offset by that counter, then
 * the option mask, and advances the work state at work+0x01 once the counter
 * reaches zero. */
MATCH void func_801D4984(void) {
    s16 key;
    s32 mask;

    SELF(FishingState)->timer--;
    Fishing_DrawCatchBar(-(SELF(FishingState)->timer * 80), FISHING_CATCH_BAR_Y);
    key = SELF(FishingState)->bounce.half.key;
    if (g_FishingBestCatch[key] != 0) {
        Fishing_DrawCatchIcon(SELF(FishingState)->timer * FISHING_CATCH_ICON_STEP + FISHING_CATCH_ICON_X, FISHING_CATCH_ICON_Y, key);
        Fishing_DrawCatchRow(SELF(FishingState)->bounce.half.key & BYTE_MASK, g_FishingBestCatch[SELF(FishingState)->bounce.half.key], SELF(FishingState)->timer);
    } else {
        Fishing_DrawCatchIcon(SELF(FishingState)->timer * FISHING_CATCH_ICON_STEP + FISHING_CATCH_ICON_X, FISHING_CATCH_ICON_Y, GAME_NONE);
        Fishing_DrawCatchRow(0xFF, 0, SELF(FishingState)->timer);
    }
    Fishing_DrawRank(FISHING_CATCH_RANK_X, SELF(FishingState)->timer * FISHING_CATCH_ROW_STEP + FISHING_CATCH_RANK_Y);
    Fishing_DrawIconRow(8, SELF(FishingState)->timer * FISHING_CATCH_ROW_STEP + FISHING_CATCH_ROW_Y, 65535);
    Fishing_DrawWindowFrame(MENU_HEADER_X, MENU_HEADER_Y, MENU_HEADER_WIDTH, MENU_HEADER_HEIGHT, 0);
    mask = 0;
    if (D_80145E93[0] >= 3u) {
        mask = BIT(SELF(FishingState)->cue_index) & BYTE_MASK;
    }
    func_801D7C10(FISHING_SHOP_COLUMNS_X, FISHING_SHOP_COLUMNS_Y, mask);
    if (SELF(FishingState)->timer == 0) {
        SELF(FishingState)->handler_index++;
    }
}

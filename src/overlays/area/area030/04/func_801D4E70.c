#include "area030_04.h"

/* Draws one panel row: counts the work timer down, draws the entry for the current key at the
 * offset set by the direction flag, then the frame, and resets the state to 8 once the timer reaches zero. */
MATCH void func_801D4E70(void) {
    FishingState* work;
    s16           key;
    s16           key_a;
    s16           key_b;
    s32           index;
    s32           mask;
    u8            fish;

    FISHING_STATE->step_timer--;
    Fishing_DrawCatchBar(0, FISHING_CATCH_BAR_Y);
    key   = FISHING_STATE->bounce.half.key;
    fish  = g_FishingBestCatch[key];
    index = key & BYTE_MASK;
    if (fish == 0) {
        index = GAME_NONE;
        fish  = 0;
    }
    Fishing_DrawCatchRow(index, fish, 0);
    work = FISHING_STATE;
    if (work->counter_08 == 0) {
        key_a = work->bounce.half.key;
        if (g_FishingBestCatch[key_a] != 0) {
            Fishing_DrawCatchIcon((work->step_timer * FISHING_CATCH_ICON_STEP) + FISHING_CATCH_ICON_X, FISHING_CATCH_ICON_Y, key_a & BYTE_MASK);
        } else {
            Fishing_DrawCatchIcon((work->step_timer * FISHING_CATCH_ICON_STEP) + FISHING_CATCH_ICON_X, FISHING_CATCH_ICON_Y, GAME_NONE);
        }
    } else {
        key_b = work->bounce.half.key;
        if (g_FishingBestCatch[key_b] != 0) {
            Fishing_DrawCatchIcon(FISHING_CATCH_ICON_X - (work->step_timer * FISHING_CATCH_ICON_STEP), FISHING_CATCH_ICON_Y, key_b & BYTE_MASK);
        } else {
            Fishing_DrawCatchIcon(FISHING_CATCH_ICON_X - (work->step_timer * FISHING_CATCH_ICON_STEP), FISHING_CATCH_ICON_Y, GAME_NONE);
        }
    }
    Fishing_DrawRank(FISHING_CATCH_RANK_X, FISHING_CATCH_RANK_Y);
    Fishing_DrawIconRow(8, FISHING_CATCH_ROW_Y, 65535);
    func_801D7B64();
    Fishing_DrawWindowFrame(MENU_HEADER_X, MENU_HEADER_Y, MENU_HEADER_WIDTH, MENU_HEADER_HEIGHT, 0);
    mask = 0;
    if (D_80145E93[0] >= 3) {
        mask = (1 << FISHING_STATE->cue_index) & BYTE_MASK;
    }
    func_801D7C10(FISHING_SHOP_COLUMNS_X, FISHING_SHOP_COLUMNS_Y, mask);
    if (FISHING_STATE->step_timer == 0) {
        FISHING_STATE->handler_index = 8;
    }
}

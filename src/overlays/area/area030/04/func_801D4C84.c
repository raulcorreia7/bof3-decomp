#include "area030_04.h"

/* Advances the area panel's slide step (unk_09) and draws the fish
 * page for fish unk_3E: its g_FishingBestCatch record byte, or id 0xFF and 0 while
 * that byte is 0, with the title sliding left in mode 0 (unk_08) and right
 * otherwise; at step 4 it makes unk_3C the current fish and advances unk_01. */
MATCH void func_801D4C84(void) {
    s32 mask;

    FISHING_STATE->step_timer_09++;
    Fishing_DrawCatchBar(0, FISHING_CATCH_BAR_Y);
    if (g_FishingBestCatch[FISHING_STATE->bounce_3C.half.key_3E] != 0) {
        func_801E1004(FISHING_STATE->bounce_3C.half.key_3E & BYTE_MASK, g_FishingBestCatch[FISHING_STATE->bounce_3C.half.key_3E], 0);
    } else {
        func_801E1004(0xFF, 0, 0);
    }
    if (FISHING_STATE->counter_08 == 0) {
        if (g_FishingBestCatch[FISHING_STATE->bounce_3C.half.key_3E] != 0) {
            Fishing_DrawCatchIcon(FISHING_CATCH_ICON_X - FISHING_STATE->step_timer_09 * FISHING_CATCH_ICON_STEP, FISHING_CATCH_ICON_Y, FISHING_STATE->bounce_3C.half.key_3E);
        } else {
            Fishing_DrawCatchIcon(FISHING_CATCH_ICON_X - FISHING_STATE->step_timer_09 * FISHING_CATCH_ICON_STEP, FISHING_CATCH_ICON_Y, GAME_NONE);
        }
    } else {
        if (g_FishingBestCatch[FISHING_STATE->bounce_3C.half.key_3E] != 0) {
            Fishing_DrawCatchIcon(FISHING_STATE->step_timer_09 * FISHING_CATCH_ICON_STEP + FISHING_CATCH_ICON_X, FISHING_CATCH_ICON_Y, FISHING_STATE->bounce_3C.half.key_3E);
        } else {
            Fishing_DrawCatchIcon(FISHING_STATE->step_timer_09 * FISHING_CATCH_ICON_STEP + FISHING_CATCH_ICON_X, FISHING_CATCH_ICON_Y, GAME_NONE);
        }
    }
    Fishing_DrawRank(FISHING_CATCH_RANK_X, FISHING_CATCH_RANK_Y);
    Fishing_DrawIconRow(8, FISHING_CATCH_ROW_Y, 65535);
    func_801D7B64();
    Fishing_DrawWindowFrame(MENU_HEADER_X, MENU_HEADER_Y, MENU_HEADER_WIDTH, MENU_HEADER_HEIGHT, 0);
    mask = 0;
    if (D_80145E93[0] >= 3) {
        mask = (1 << FISHING_STATE->cue_index_06) & BYTE_MASK;
    }
    func_801D7C10(FISHING_SHOP_COLUMNS_X, FISHING_SHOP_COLUMNS_Y, mask);
    if (FISHING_STATE->step_timer_09 == 4) {
        FISHING_STATE->bounce_3C.half.key_3E = FISHING_STATE->bounce_3C.half.unk_3C;
        FISHING_STATE->handler_index_01++;
    }
}

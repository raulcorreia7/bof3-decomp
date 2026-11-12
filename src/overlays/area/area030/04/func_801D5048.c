#include "area030_04.h"

/* Draws one row of the rotating status display. */
MATCH void func_801D5048(void) {
    s32 mask;
    u8  height;

    height = MENU_HEADER_HEIGHT;
    if (FISHING_STATE->saved_index_0B == 0) {
        Fishing_DrawWindowFrame(MENU_HEADER_X, (MENU_HEADER_Y - (FISHING_STATE->step_timer_09 * FISHING_HEADER_SLIDE_STEP)) & 0xFFFE, MENU_HEADER_WIDTH, height, 0);
        mask = 0;
        func_801D7C10(((FISHING_STATE->step_timer_09 * FISHING_SHOP_SLIDE_STEP) + FISHING_SHOP_COLUMNS_X) & HALF_MASK, FISHING_SHOP_COLUMNS_Y, 0);
        goto draw; /* the shared tail draws the row once, from either arm */
    }
    Fishing_DrawWindowFrame(MENU_HEADER_X, MENU_HEADER_Y, MENU_HEADER_WIDTH, height, 0);
    if (D_80145E93[0] >= 3) {
        mask = (1 << FISHING_STATE->cue_index_06) & BYTE_MASK;
    } else {
        mask = 0;
    }
    func_801D7C10(FISHING_SHOP_COLUMNS_X, FISHING_SHOP_COLUMNS_Y, mask);
draw:
    FISHING_STATE->step_timer_09++;
    Fishing_DrawCatchBar((-(FISHING_STATE->step_timer_09 * TO_COORD(80)) >> 0x10), FISHING_CATCH_BAR_Y);
    if (g_FishingBestCatch[FISHING_STATE->bounce_3C.half.key_3E] != 0) {
        Fishing_DrawCatchIcon(FISHING_STATE->step_timer_09 * FISHING_CATCH_ICON_STEP + FISHING_CATCH_ICON_X, FISHING_CATCH_ICON_Y, FISHING_STATE->bounce_3C.half.key_3E & BYTE_MASK);
        func_801E1004(FISHING_STATE->bounce_3C.half.key_3E & BYTE_MASK, g_FishingBestCatch[FISHING_STATE->bounce_3C.half.key_3E], FISHING_STATE->step_timer_09);
    } else {
        Fishing_DrawCatchIcon(FISHING_STATE->step_timer_09 * FISHING_CATCH_ICON_STEP + FISHING_CATCH_ICON_X, FISHING_CATCH_ICON_Y, GAME_NONE);
        func_801E1004(0xFF, 0, FISHING_STATE->step_timer_09);
    }
    Fishing_DrawRank(FISHING_CATCH_RANK_X, FISHING_STATE->step_timer_09 * FISHING_CATCH_ROW_STEP + FISHING_CATCH_RANK_Y);
    Fishing_DrawIconRow(8, FISHING_STATE->step_timer_09 * FISHING_CATCH_ROW_STEP + FISHING_CATCH_ROW_Y, 65535);
    if (FISHING_STATE->step_timer_09 == 4) {
        if (FISHING_STATE->saved_index_0B == 0) {
            FISHING_STATE->handler_index_01 = 0;
        } else if (FISHING_STATE->cue_index_06 == 0) {
            FISHING_STATE->handler_index_01 = 2;
        } else if (FISHING_STATE->cue_index_06 == 2) {
            FISHING_STATE->handler_index_01++;
        }
    }
}

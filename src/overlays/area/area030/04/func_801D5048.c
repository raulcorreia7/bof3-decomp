#include "area030_04.h"

/* Draws one row of the rotating status display. */
MATCH void func_801D5048(void) {
    s32 mask;
    u8  height;

    height = MENU_HEADER_HEIGHT;
    if (FISHING_STATE->saved_index == 0) {
        Fishing_DrawWindowFrame(MENU_HEADER_X, (MENU_HEADER_Y - (FISHING_STATE->step_timer * FISHING_HEADER_SLIDE_STEP)) & 0xFFFE, MENU_HEADER_WIDTH, height, 0);
        mask = 0;
        func_801D7C10(((FISHING_STATE->step_timer * FISHING_SHOP_SLIDE_STEP) + FISHING_SHOP_COLUMNS_X) & HALF_MASK, FISHING_SHOP_COLUMNS_Y, 0);
        goto draw; /* the shared tail draws the row once, from either arm */
    }
    Fishing_DrawWindowFrame(MENU_HEADER_X, MENU_HEADER_Y, MENU_HEADER_WIDTH, height, 0);
    if (D_80145E93[0] >= 3) {
        mask = (1 << FISHING_STATE->cue_index) & BYTE_MASK;
    } else {
        mask = 0;
    }
    func_801D7C10(FISHING_SHOP_COLUMNS_X, FISHING_SHOP_COLUMNS_Y, mask);
draw:
    FISHING_STATE->step_timer++;
    Fishing_DrawCatchBar((-(FISHING_STATE->step_timer * TO_COORD(80)) >> 0x10), FISHING_CATCH_BAR_Y);
    if (g_FishingBestCatch[FISHING_STATE->bounce.half.key] != 0) {
        Fishing_DrawCatchIcon(FISHING_STATE->step_timer * FISHING_CATCH_ICON_STEP + FISHING_CATCH_ICON_X, FISHING_CATCH_ICON_Y, FISHING_STATE->bounce.half.key & BYTE_MASK);
        Fishing_DrawCatchRow(FISHING_STATE->bounce.half.key & BYTE_MASK, g_FishingBestCatch[FISHING_STATE->bounce.half.key], FISHING_STATE->step_timer);
    } else {
        Fishing_DrawCatchIcon(FISHING_STATE->step_timer * FISHING_CATCH_ICON_STEP + FISHING_CATCH_ICON_X, FISHING_CATCH_ICON_Y, GAME_NONE);
        Fishing_DrawCatchRow(0xFF, 0, FISHING_STATE->step_timer);
    }
    Fishing_DrawRank(FISHING_CATCH_RANK_X, FISHING_STATE->step_timer * FISHING_CATCH_ROW_STEP + FISHING_CATCH_RANK_Y);
    Fishing_DrawIconRow(8, FISHING_STATE->step_timer * FISHING_CATCH_ROW_STEP + FISHING_CATCH_ROW_Y, 65535);
    if (FISHING_STATE->step_timer == 4) {
        if (FISHING_STATE->saved_index == 0) {
            FISHING_STATE->handler_index = 0;
        } else if (FISHING_STATE->cue_index == 0) {
            FISHING_STATE->handler_index = 2;
        } else if (FISHING_STATE->cue_index == 2) {
            FISHING_STATE->handler_index++;
        }
    }
}

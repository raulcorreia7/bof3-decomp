#include "area030_04.h"

/* Advances the area panel's cursor step and draws its rows: the
 *           0x0B mode picks the full-width or indented row band, the 0x07 flag
 *           picks the normal or alternate row renderer, and at step 4 the mode
 *           sets the next cursor byte (advance or 0xC). */
MATCH void func_801D4680(void) {
    s32 x;
    s32 y;
    s32 t;
    s32 flags;

    TASK(FishingState)->step_timer++;
    if (TASK(FishingState)->saved_index == 0) {
        Fishing_DrawWindowFrame(MENU_HEADER_X, (MENU_HEADER_Y - (TASK(FishingState)->step_timer * 16)) & 0xFFFE, MENU_HEADER_WIDTH, MENU_HEADER_HEIGHT, 0U);
        y     = FISHING_SHOP_COLUMNS_Y;
        flags = 0;
        t     = TASK(FishingState)->step_timer * 3;
        x     = t << 4;
        x -= t;
        x += FISHING_SHOP_COLUMNS_X;
        x &= HALF_MASK;
    } else {
        Fishing_DrawWindowFrame(MENU_HEADER_X, MENU_HEADER_Y, MENU_HEADER_WIDTH, MENU_HEADER_HEIGHT, 0U);
        flags = 0;
        if (D_80145E93[0] >= 3) {
            flags = (1 << TASK(FishingState)->cue_index) & BYTE_MASK;
        }
        x = FISHING_SHOP_COLUMNS_X;
        y = FISHING_SHOP_COLUMNS_Y;
    }
    func_801D7C10(x, y, flags);
    func_801D88E0((FISHING_EQUIP_PANEL_X - (TASK(FishingState)->step_timer * FISHING_SHOP_SLIDE_STEP)), FISHING_PANEL_CONTENT_Y);
    if (!(TASK(FishingState)->counter_07 & 0x1)) {
        func_801D7EB0((s16)((TASK(FishingState)->step_timer * FISHING_SHOP_SLIDE_STEP) + FISHING_ITEM_PANEL_X), FISHING_PANEL_CONTENT_Y);
    } else {
        func_801D8364(((TASK(FishingState)->step_timer * FISHING_SHOP_SLIDE_STEP) + FISHING_ITEM_PANEL_X), FISHING_PANEL_CONTENT_Y);
    }
    if (TASK(FishingState)->step_timer == 4) {
        if (TASK(FishingState)->saved_index == 0) {
            TASK(FishingState)->handler_index = 0;
            return;
        }
        if (TASK(FishingState)->cue_index == 1) {
            TASK(FishingState)->handler_index++;
        } else if (TASK(FishingState)->cue_index == 2) {
            TASK(FishingState)->handler_index = 0xC;
        }
    }
}

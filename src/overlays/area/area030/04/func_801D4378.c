#include "area030_04.h"

/* Steps the area panel back one cursor row (unk_09); when it reaches
 * row 0 it sets the 0x0B mode and moves unk_01 to the next state, or to 4
 * when bit 0 of unk_07 is set. It then draws the panel frame and rows at the
 * row offset, the selection mask (1 << unk_06) appearing only in mode 0x0B
 * once D_80145E93 is at least 3. */
MATCH void func_801D4378(void) {
    s32 mask;

    SELF(FishingState)->timer--;
    if (SELF(FishingState)->timer == 0) {
        SELF(FishingState)->saved_index = 1;
        if (!(SELF(FishingState)->counter_07 & 0x1)) {
            SELF(FishingState)->handler_index++;
        } else {
            SELF(FishingState)->handler_index = 4;
        }
    }
    if (SELF(FishingState)->saved_index == 0) {
        Fishing_DrawWindowFrame(MENU_HEADER_X, (MENU_HEADER_Y - SELF(FishingState)->timer * 16) & 0xFFFE, MENU_HEADER_WIDTH, MENU_HEADER_HEIGHT, 0);
        func_801D7C10((u16)(SELF(FishingState)->timer * FISHING_SHOP_SLIDE_STEP + FISHING_SHOP_COLUMNS_X), FISHING_SHOP_COLUMNS_Y, 0);
    } else {
        Fishing_DrawWindowFrame(MENU_HEADER_X, MENU_HEADER_Y, MENU_HEADER_WIDTH, MENU_HEADER_HEIGHT, 0);
        mask = 0;
        if (D_80145E93[0] >= 3) {
            mask = (1 << SELF(FishingState)->cue_index) & BYTE_MASK;
        }
        func_801D7C10(FISHING_SHOP_COLUMNS_X, FISHING_SHOP_COLUMNS_Y, mask);
    }
    func_801D88E0(FISHING_EQUIP_PANEL_X - SELF(FishingState)->timer * FISHING_SHOP_SLIDE_STEP, FISHING_PANEL_CONTENT_Y);
    if (!(SELF(FishingState)->counter_07 & 0x1)) {
        func_801D7EB0((s16)(SELF(FishingState)->timer * FISHING_SHOP_SLIDE_STEP + FISHING_ITEM_PANEL_X), FISHING_PANEL_CONTENT_Y);
    } else {
        func_801D8364(SELF(FishingState)->timer * FISHING_SHOP_SLIDE_STEP + FISHING_ITEM_PANEL_X, FISHING_PANEL_CONTENT_Y);
    }
}

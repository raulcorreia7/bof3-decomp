#include "area030_04.h"

/* Runs the panel helper, derives the option mask from the scratch
 * record byte at +6 when the progress counter reaches 3, then issues the two
 * panel draws. */
MATCH void func_801D54F8(void) {
    FishingState* record;
    s32           mask;

    Fishing_DrawWindowFrame(MENU_HEADER_X, MENU_HEADER_Y, MENU_HEADER_WIDTH, MENU_HEADER_HEIGHT, 0);
    mask = 0;
    if (D_80145E93[0] >= 3u) {
        record = FISHING_STATE;
        mask   = BIT(record->cue_index_06) & BYTE_MASK;
    }
    func_801D7C10(FISHING_SHOP_COLUMNS_X, FISHING_SHOP_COLUMNS_Y, mask);
    func_801D72E4(39, 64);
}

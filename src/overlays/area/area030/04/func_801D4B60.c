#include "area030_04.h"

/* Draws the AREA030 fishing panel. */
MATCH void func_801D4B60(void) {
    s16 key;
    u8  fish;
    s32 mask;

    func_801E0ED0(0, FISHING_CATCH_BAR_Y);
    key  = FISHING_STATE->bounce_3C.half.key_3E;
    fish = g_FishingBestCatch[key];
    if (fish != 0) {
        func_801E1004(key & BYTE_MASK, fish, 0);
        func_801E0F4C(FISHING_CATCH_ICON_X, FISHING_CATCH_ICON_Y, FISHING_STATE->bounce_3C.half.key_3E);
        Fishing_DrawIconRow(8, FISHING_CATCH_ROW_Y, FISHING_STATE->bounce_3C.half.key_3E);
    } else {
        func_801E1004(0xFF, 0, 0);
        func_801E0F4C(FISHING_CATCH_ICON_X, FISHING_CATCH_ICON_Y, 0xFF);
        Fishing_DrawIconRow(8, FISHING_CATCH_ROW_Y, 0xFFFF);
    }
    Fishing_DrawRank(FISHING_CATCH_RANK_X, FISHING_CATCH_RANK_Y);
    func_801D7B64();
    func_801D9534(MENU_HEADER_X, MENU_HEADER_Y, MENU_HEADER_WIDTH, MENU_HEADER_HEIGHT, 0);
    mask = 0;
    if (D_80145E93[0] >= 3u) {
        mask = BIT(FISHING_STATE->cue_index_06) & BYTE_MASK;
    }
    func_801D7C10(FISHING_SHOP_COLUMNS_X, FISHING_SHOP_COLUMNS_Y, mask);
}

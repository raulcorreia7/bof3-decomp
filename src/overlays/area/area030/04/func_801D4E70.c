#include "area030_04.h"

/* Draws one panel row: counts the work timer down, draws the entry for the current key at the offset set by the direction flag. */
MATCH void func_801D4E70(void) {
    FishingState* work;
    s16           key;
    s16           key_a;
    s16           key_b;
    s32           index;
    s32           mask;
    u8            fish;

    FISHING_STATE->step_timer_09--;
    func_801E0ED0(0, FISHING_CATCH_BAR_Y);
    key   = FISHING_STATE->bounce_3C.half.key_3E;
    fish  = g_FishingBestCatch[key];
    index = key & BYTE_MASK;
    if (fish == 0) {
        index = 0xFF;
        fish  = 0;
    }
    func_801E1004(index, fish, 0);
    work = FISHING_STATE;
    if (work->counter_08 == 0) {
        key_a = work->bounce_3C.half.key_3E;
        if (g_FishingBestCatch[key_a] != 0) {
            func_801E0F4C((work->step_timer_09 * FISHING_CATCH_ICON_STEP) + FISHING_CATCH_ICON_X, FISHING_CATCH_ICON_Y,
                          key_a & BYTE_MASK);
        } else {
            func_801E0F4C((work->step_timer_09 * FISHING_CATCH_ICON_STEP) + FISHING_CATCH_ICON_X, FISHING_CATCH_ICON_Y,
                          0xFF);
        }
    } else {
        key_b = work->bounce_3C.half.key_3E;
        if (g_FishingBestCatch[key_b] != 0) {
            func_801E0F4C(FISHING_CATCH_ICON_X - (work->step_timer_09 * FISHING_CATCH_ICON_STEP), FISHING_CATCH_ICON_Y,
                          key_b & BYTE_MASK);
        } else {
            func_801E0F4C(FISHING_CATCH_ICON_X - (work->step_timer_09 * FISHING_CATCH_ICON_STEP), FISHING_CATCH_ICON_Y,
                          0xFF);
        }
    }
    Fishing_DrawRank(FISHING_CATCH_RANK_X, FISHING_CATCH_RANK_Y);
    Fishing_DrawIconRow(8, FISHING_CATCH_ROW_Y, 0xFFFF);
    func_801D7B64();
    func_801D9534(MENU_HEADER_X, MENU_HEADER_Y, MENU_HEADER_WIDTH, MENU_HEADER_HEIGHT, 0);
    mask = 0;
    if (D_80145E93[0] >= 3) {
        mask = (1 << FISHING_STATE->cue_index_06) & BYTE_MASK;
    }
    func_801D7C10(FISHING_SHOP_COLUMNS_X, FISHING_SHOP_COLUMNS_Y, mask);
    if (FISHING_STATE->step_timer_09 == 0) {
        FISHING_STATE->handler_index_01 = 8;
    }
}

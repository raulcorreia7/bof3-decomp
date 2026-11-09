#include "area030_04.h"

/* Panel cursor fields of the scratchpad work record. */
#define FISHING_CURSOR_TIMER    (FISHING_STATE->step_timer_09)
#define FISHING_CURSOR_ROW_Y    (FISHING_STATE->origin_x_2E)
#define FISHING_CURSOR_ITEM_PTR (FISHING_STATE->item_50.pointer)
#define FISHING_CURSOR_COUNT    (FISHING_STATE->counter_49)
#define FISHING_CURSOR_CATEGORY (FISHING_STATE->row_4B)
#define FISHING_CURSOR_FLAG     (FISHING_STATE->step_index_0A)
#define FISHING_CURSOR_STEP     (FISHING_STATE->handler_index_01)

/* Ticks the AREA030 panel item cursor: counts the entry timer down and draws the shrinking row, or on expiry
 * skips a two-byte item code, advances the item pointer and entry count, clamps the count to the category table and
 * hands the new category row to the cursor. */
MATCH void func_801D3A54(void) {
    FishingState* work;
    u8*           item;
    u8            max;
    u8            entry_count;
    u8*           item_next;

    work = FISHING_STATE;
    work->step_timer_09 -= 1;
    work->origin_x_2E -= 2;
    if (FISHING_CURSOR_TIMER == 0) {
        item = (u8*)FISHING_CURSOR_ITEM_PTR;
        if (*item == 0x12 || *item == 0x15) {
            FISHING_CURSOR_ITEM_PTR = item + 1;
        }
        entry_count             = FISHING_CURSOR_COUNT + 1;
        item_next               = FISHING_CURSOR_ITEM_PTR + 1;
        FISHING_CURSOR_ITEM_PTR = item_next;
        FISHING_CURSOR_COUNT    = entry_count;
        FISHING_CURSOR_TIMER    = 4;
        max                     = D_801E1E78[FISHING_CURSOR_CATEGORY * 0xC];
        if (FISHING_CURSOR_COUNT >= max) {
            FISHING_CURSOR_COUNT = max;
            if (D_801E1E80[FISHING_CURSOR_CATEGORY * 0xC] != GAME_NONE) {
                FISHING_CURSOR_FLAG = 4;
            } else {
                FISHING_CURSOR_FLAG = 0;
            }
            FISHING_CURSOR_TIMER    = D_801E1E80[FISHING_CURSOR_CATEGORY * 0xC + 1];
            FISHING_CURSOR_ITEM_PTR = (u8*)D_801E1E7C[FISHING_CURSOR_CATEGORY * 3];
            FISHING_CURSOR_STEP += 1;
        }
    } else {
        func_801D9740(0, (u8*)FISHING_CURSOR_ITEM_PTR, (8 - FISHING_CURSOR_TIMER * 2) & 0xFE, FISHING_CURSOR_TIMER * 2 + 0x11D);
    }
    if (FISHING_CURSOR_COUNT != 0) {
        UI_DrawText(FISHING_CURSOR_ROW_Y, (D_80144154 + 2), 0, FISHING_CURSOR_COUNT, (u8*)(D_801E1E7C[FISHING_CURSOR_CATEGORY * 3]));
    }
}

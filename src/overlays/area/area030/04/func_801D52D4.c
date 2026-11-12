#include "area030_04.h"

/* Draws a fixed frame, passes a bit selected by work byte 6 when
 * D_80145E93 is at least 3, then resets work fields and increments byte 1. */
MATCH void func_801D52D4(void) {
    FishingState* work;
    FishingState* stepped;
    u32           mask;

    Fishing_DrawWindowFrame(MENU_HEADER_X, MENU_HEADER_Y, MENU_HEADER_WIDTH, MENU_HEADER_HEIGHT, 0);

    mask = 0;
    if (D_80145E93[0] >= 3) {
        mask = (1u << g_Task->unk_06) & BYTE_MASK;
    }
    func_801D7C10(FISHING_SHOP_COLUMNS_X, FISHING_SHOP_COLUMNS_Y, mask);

    g_Task->direction_08   = FACING_UP_LEFT;
    work                   = FISHING_STATE;
    work->step_index_0A    = 0;
    stepped                = FISHING_STATE;
    work->bounce_3C.unk_3C = 0;
    work->step_14          = 0;
    work->step_limit_20    = 0;
    stepped->step_timer_09 = 4;
    g_Task->header.mode    = (u8)(g_Task->header.mode + 1);
}

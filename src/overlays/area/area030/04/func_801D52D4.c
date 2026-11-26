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
        mask = (1u << SELF(Actor)->unk_06) & BYTE_MASK;
    }
    func_801D7C10(FISHING_SHOP_COLUMNS_X, FISHING_SHOP_COLUMNS_Y, mask);

    SELF(Actor)->direction   = FACING_UP_LEFT;
    work                     = SELF(FishingState);
    work->step_index         = 0;
    stepped                  = SELF(FishingState);
    work->bounce.unk_3C      = 0;
    work->bounce_speed       = 0;
    work->bounce_accel       = 0;
    stepped->timer           = 4;
    SELF(Actor)->header.mode = (u8)(SELF(Actor)->header.mode + 1);
}

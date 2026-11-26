#include "area030_04.h"

/* Advances the local scratch vertical offset, wraps it at the panel
 * limit while stepping the state byte, then routes the panel draw through the
 * helper at `0x801D9534`. */
/* func_801D3684 */
MATCH void Fishing_PromptSlideIn(void) {
    s32 val;

    val                          = SELF(FishingState)->origin_y + 8;
    SELF(FishingState)->origin_y = val;

    if ((s16)val >= 0x13) {
        SELF(FishingState)->origin_y      = 0x12;
        SELF(FishingState)->handler_index = (SELF(FishingState)->handler_index + 1);
    }

    Fishing_DrawWindowFrame(MENU_HEADER_X, SELF(FishingState)->origin_y, MENU_HEADER_WIDTH, MENU_HEADER_HEIGHT, 0);
}

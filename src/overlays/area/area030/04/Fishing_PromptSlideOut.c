#include "area030_04.h"

/* Advances the local scratch vertical offset and routes the next
 * AREA030 panel draw through the later helper at `0x801D9534`. */
/* func_801D3938 */
MATCH void Fishing_PromptSlideOut(void) {
    s32 val;

    val                          = SELF(FishingState)->origin_y - 8;
    SELF(FishingState)->origin_y = val;

    if ((s16)val < -0x19) {
        if (SELF(FishingState)->counter_07 != 0u) {
            SELF(FishingState)->handler_index = 1u;
        } else {
            SELF(FishingState)->handler_index = 0u;
        }
    }

    Fishing_DrawWindowFrame(MENU_HEADER_X, SELF(FishingState)->origin_y, MENU_HEADER_WIDTH, MENU_HEADER_HEIGHT, 0);
}

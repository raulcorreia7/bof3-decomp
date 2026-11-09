#include "area030_04.h"

/* Advances the local scratch vertical offset, wraps it at the panel limit while stepping the state byte. */
/* func_801D3684 */
MATCH void Fishing_PromptSlideIn(void) {
    s32 val;

    val                        = FISHING_STATE->origin_y_30 + 8;
    FISHING_STATE->origin_y_30 = val;

    if ((s16)val >= 0x13) {
        FISHING_STATE->origin_y_30      = 0x12;
        FISHING_STATE->handler_index_01 = (FISHING_STATE->handler_index_01 + 1);
    }

    func_801D9534(MENU_HEADER_X, FISHING_STATE->origin_y_30, MENU_HEADER_WIDTH, MENU_HEADER_HEIGHT, 0);
}

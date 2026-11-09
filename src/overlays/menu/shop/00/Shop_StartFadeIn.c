#include "shop_00.h"

/* File-local declaration: UI_SetMode is the game UI mode setter owned by the game UI contract (include/sys/gameui.h) and is not declared by shop_00.h. */

/* func_801DE3C8 */
MATCH void Shop_StartFadeIn(void) {
    volatile u8* counter;
    u8           count;

    if (WINDOW_EFFECT_IDLE()) {
        UI_SetMode(UI_MODE_FAST_FADE_IN);
        counter  = &g_MenuStep.state;
        count    = *counter;
        *counter = count + 1;
    }
}

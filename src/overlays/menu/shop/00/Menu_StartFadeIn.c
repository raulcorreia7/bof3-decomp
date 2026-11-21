#include "shop_00.h"

/* File-local declaration: UI_ModeSet is the game UI mode setter owned by
 * the game UI contract (include/menu/gameui.h) and is not declared by
 * shop_00.h. */

/* func_801DE3C8 */
MATCH void Menu_StartFadeIn(void) {
    volatile u8* counter;
    u8           count;

    if (WINDOW_EFFECT_IDLE()) {
        UI_ModeSet(UI_MODE_FAST_FADE_IN);
        counter  = &g_MenuStep.state;
        count    = *counter;
        *counter = count + 1;
    }
}

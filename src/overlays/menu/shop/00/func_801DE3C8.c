#include "shop_00.h"

/* File-local declaration: UI_SetMode is the game UI mode setter owned by
 * the game UI contract (include/sys/gameui.h) and is not declared by
 * shop_00.h. */

MATCH void func_801DE3C8(void) {
    volatile u8* counter;
    u8           count;

    if (WINDOW_EFFECT_IDLE()) {
        UI_SetMode(UI_MODE_FAST_FADE_IN);
        counter  = &D_80148652;
        count    = *counter;
        *counter = count + 1;
    }
}

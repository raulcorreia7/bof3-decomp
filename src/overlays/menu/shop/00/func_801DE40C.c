#include "shop_00.h"

MATCH void func_801DE40C(void) {
    u8* counter;
    u8  count;

    func_801DF6A8();
    if (WINDOW_EFFECT_IDLE()) {
        counter          = &g_MenuStep.sub_step;
        count            = *counter;
        g_MenuStep.state = 0;
        *counter         = count + 2;
    }
}

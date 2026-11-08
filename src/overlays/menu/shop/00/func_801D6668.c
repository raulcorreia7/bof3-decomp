#include "shop_00.h"

MATCH void func_801D6668(void) {
    volatile u8* state;

    if (WINDOW_EFFECT_IDLE()) {
        func_801D68D0(0);
        state = &g_MenuStep.sub_step;
        *state += 1;
    }
}

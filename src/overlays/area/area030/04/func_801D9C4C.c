#include "area030_04.h"

/* When halfword `g_UiWindowEffectBusy` is clear, clears byte `D_8014419E`, increments byte `D_80144199`. */
MATCH void func_801D9C4C(void) {
    u8* p;

    if (WINDOW_EFFECT_IDLE()) {
        D_8014419E = 0;
        p          = &D_80144199;
        *p         = (*p + 1);
        FISHING_STATE->sub_index_03 += 1;
    }
}

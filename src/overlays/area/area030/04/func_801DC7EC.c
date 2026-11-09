#include "area030_04.h"

/* When halfword `g_UiWindowEffectBusy` is clear, initializes the scratchpad work object. */
MATCH void func_801DC7EC(void) {
    if (WINDOW_EFFECT_IDLE()) {
        FISHING_STATE->mode_index_02 = 1;
        FISHING_STATE->sub_index_03  = 0;
        FISHING_STATE->flag_04       = 0;
    }
}

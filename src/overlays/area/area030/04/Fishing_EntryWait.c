#include "area030_04.h"

/* When halfword `g_UiWindowEffectBusy` is clear, clears byte `D_8014419E`,
 * increments byte `D_80144199`, then increments byte 0x03 of the scratchpad
 * work object. */
/* func_801D9C4C */
MATCH void Fishing_EntryWait(void) {
    u8* p;

    if (WINDOW_EFFECT_IDLE()) {
        D_8014419E = 0;
        p          = &D_80144199;
        *p         = (*p + 1);
        FISHING_STATE->sub_index_03 += 1;
    }
}

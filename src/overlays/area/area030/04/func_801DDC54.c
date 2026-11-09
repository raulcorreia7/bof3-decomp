#include "area030_04.h"

/* When the state halfword is clear, clears the four companion overlay flags and the mode byte, arms the state halfword with 3. */
MATCH void func_801DDC54(void) {
    FishingState* spad;

    if (WINDOW_EFFECT_IDLE()) {
        spad                = FISHING_STATE;
        D_800F724C          = 0;
        D_800F724D          = 0;
        D_800F724E          = 0;
        D_800F724F          = 0;
        g_AreaDrawFlags     = 0;
        g_GameEntrySubstate = 3;
        spad->sub_index_03  = (spad->sub_index_03 + 1u);
    }
}

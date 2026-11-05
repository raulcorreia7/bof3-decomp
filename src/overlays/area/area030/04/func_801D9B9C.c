#include "area030_04.h"

/* Resets the AREA030 anchor flags, stores the probe height from the
 * scratch position pair and arms either the long or the short settle step before
 * stepping the work state. */
MATCH void func_801D9B9C(void) {
    FishingState* work;
    FishingState* state;
    u8*           panel;
    s16           distance;
    u8            flag;

    D_801E3200 = 0;
    D_801E3204 = 0;
    D_801E3214 = 0;

    work           = FISHING_STATE;
    work->state_29 = 5;

    state    = FISHING_STATE;
    distance = Area_SampleHeight(state->motion_34.unk_34, state->y_38.pos_y);

    panel                                = g_GameState;
    FISHING_STATE->bounce_3C.half.key_3E = distance;
    flag                                 = panel[0x79];
    if (flag == 0) {
        Actor_BeginScript(0xA, 2);
    } else {
        Actor_SelectScript(0xB);
    }

    work               = FISHING_STATE;
    work->sub_index_03 = (work->sub_index_03 + 1);
}

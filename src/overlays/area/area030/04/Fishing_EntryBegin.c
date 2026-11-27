#include "area030_04.h"

/* Resets the AREA030 anchor flags, stores the probe height from the
 * scratch position pair and arms either the long or the short settle step before
 * stepping the work state. */
/* func_801D9B9C */
MATCH void Fishing_EntryBegin(void) {
    FishingState* work;
    FishingState* state;
    u8*           panel;
    s16           distance;
    u8            flag;

    D_801E3200               = 0;
    g_FishingFullNoticeShown = 0;
    g_FishingNewRecord       = 0;

    work           = SELF(FishingState);
    work->state_29 = 5;

    state    = SELF(FishingState);
    distance = Area_HeightSample(state->motion.unk_34, state->y_38.pos_y);

    panel                               = g_Game.current;
    SELF(FishingState)->bounce.half.key = distance;
    flag                                = panel[0x79];
    if (flag == 0) {
        Script_Begin(0xA, 2);
    } else {
        Script_Select(0xB);
    }

    work            = SELF(FishingState);
    work->sub_index = (work->sub_index + 1);
}

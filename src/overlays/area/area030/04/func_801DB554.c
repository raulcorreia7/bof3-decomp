#include "area030_04.h"

/* On the final counter state raises the per-slot gauge to its limit
 * and arms the panel cue, then refreshes the shared panel helper. */
MATCH void func_801DB554(void) {
    FishingState* record;
    u8            value;
    u16           limit;

    if (D_80144199 == 4) {
        value = g_Actors[D_801E3208].unk_06;
        limit = g_Actors[D_801E3208].roll_90;
        if (g_FishBestCatch[value] < limit) {
            g_FishBestCatch[value] = (u8)limit;
            D_801E3214                      = 1;
        }

        SND_PlayCue(EMI_CUE_ID(1, 2));

        record                = FISHING_STATE;
        record->step_timer_09 = 8;

        record               = FISHING_STATE;
        record->sub_index_03 = (u8)(record->sub_index_03 + 1);
    }

    func_8014D978();
}

#include "area030_04.h"

/* On the final counter state raises the per-slot gauge to its limit
 * and arms the panel cue, then refreshes the shared panel helper. */
/* func_801DB554 */
MATCH void Fishing_CatchRecord(void) {
    FishingState* record;
    u8            value;
    u16           limit;

    if (D_80144199 == 4) {
        value = g_Actors[g_FishingHookedFish].unk_06;
        limit = g_Actors[g_FishingHookedFish].roll_90;
        if (g_FishBestCatch[value] < limit) {
            g_FishBestCatch[value] = limit;
            g_FishingNewRecord     = 1;
        }

        SND_PlayCue(EMI_CUE_ID(1, 2));

        record                = FISHING_STATE;
        record->step_timer_09 = 8;

        record               = FISHING_STATE;
        record->sub_index_03 = (record->sub_index_03 + 1);
    }

    func_8014D978();
}

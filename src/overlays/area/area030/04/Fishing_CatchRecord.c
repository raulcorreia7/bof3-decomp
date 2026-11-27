#include "area030_04.h"

/* On the final counter state raises the per-slot gauge to its limit
 * and arms the panel cue, then refreshes the shared panel helper. */
/* func_801DB554 */
MATCH void Fishing_CatchRecord(void) {
    FishingState* record;
    u8            value;
    u16           limit;

    if (g_SpawnedActors[4].header.mode == 4) {
        value = g_Actors[g_FishingHookedFish].unk_06;
        limit = g_Actors[g_FishingHookedFish].roll_90;
        if (g_FishingBestCatch[value] < limit) {
            g_FishingBestCatch[value] = limit;
            g_FishingNewRecord        = 1;
        }

        SND_SEPlay(EMI_SE_ID(SND_BANK_COMMON, 2));

        record        = SELF(FishingState);
        record->timer = 8;

        record            = SELF(FishingState);
        record->sub_index = (record->sub_index + 1);
    }

    Script_AnimStepLoop();
}

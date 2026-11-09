#include "area030_04.h"

/* Decrements the scratchpad panel counter, shifts the panel by the
 * counter's remaining pixels, and once the counter reaches zero queues cue
 * 0x20B or 0x20C according to the current slot's stored type, reloads the
 * counter to 4 and advances the panel state before the world step passes. */
MATCH void func_801DB620(void) {
    FishingState* record;
    u8            slot;
    u16           cue;

    record                = FISHING_STATE;
    record->step_timer_09 = (record->step_timer_09 - 1);
    func_801E0ED0((-(FISHING_STATE->step_timer_09 * TO_COORD(40)) >> 16), FISHING_CATCH_BAR_Y);
    if (FISHING_STATE->step_timer_09 == 0) {
        slot = D_8014688E[g_FishingHookedFish * 0x98];
        cue  = 0x20B;
        if (D_801E2AD5[slot * 0x24] >= 2) {
            cue = 0x20C;
        }
        SND_PlayCue(cue);
        FISHING_STATE->step_timer_09 = 4;
        record                       = FISHING_STATE;
        record->sub_index_03         = (record->sub_index_03 + 1);
    }
    Actor_StepAnimLoop();
    func_801E16DC();
}

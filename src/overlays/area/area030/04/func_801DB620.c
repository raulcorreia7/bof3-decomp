#include "area030_04.h"

/* Decrements the scratchpad panel counter, shifts the panel by the
 * counter's remaining pixels, and once the counter reaches zero queues cue
 * 0x20B or 0x20C according to the current slot's stored type, reloads the
 * counter to 4 and advances the panel state before the world step passes. */
MATCH void func_801DB620(void) {
    FishingState* record;
    u8            slot;
    u16           cue;

    record             = TASK(FishingState);
    record->step_timer = (record->step_timer - 1);
    Fishing_DrawCatchBar((-(TASK(FishingState)->step_timer * TO_COORD(40)) >> 16), FISHING_CATCH_BAR_Y);
    if (TASK(FishingState)->step_timer == 0) {
        slot = D_8014688E[g_FishingHookedFish * 0x98];
        cue  = 0x20B;
        if (D_801E2AD5[slot * 0x24] >= 2) {
            cue = 0x20C;
        }
        SND_SEPlay(cue);
        TASK(FishingState)->step_timer = 4;
        record                         = TASK(FishingState);
        record->sub_index              = (record->sub_index + 1);
    }
    Script_AnimStepLoop();
    Fishing_DrawDimScreen();
}

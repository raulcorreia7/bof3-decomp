#include "area030_04.h"

/* When the state byte is clear and the flag byte is 1, seeds the
 * work counter, queues cue 0x102, and bumps the work phase. */
/* func_801D9FE8 */
MATCH void Fishing_ReadyPrompt(void) {
    if (D_80144125 == 0 && D_8014403D == 1) {
        FISHING_STATE->step_timer_09 = 4;
        SND_PlayCue(EMI_CUE_ID(SND_BANK_COMMON, 2));
        FISHING_STATE->sub_index_03 += 1;
    }
    Fishing_DrawDimScreen();
}

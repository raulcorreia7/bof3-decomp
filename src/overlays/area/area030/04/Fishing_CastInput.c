#include "area030_04.h"

/* Reacts to the confirm/cancel pad bits for the AREA030 prompt. */
/* func_801DA638 */
MATCH void Fishing_CastInput(void) {
    FishingState* work;
    FishingState* tail;
    FishingState* state;
    FishingState* next;

    if ((g_InputPressed & g_InputMasks[FISHING_INPUT_CAST]) != 0) {
        D_801440C8 = 0;
        SND_PlayCue(EMI_CUE_ID(SND_BANK_AREA, 0));
        D_801E31FC = 0xFF;
        D_801E31F8 = 0xFF;
        Actor_RequestScript(2);

        work                = FISHING_STATE;
        work->y_38.pos_y    = TO_COORD(65);
        work->step_timer_09 = 0;

        tail               = FISHING_STATE;
        tail->sub_index_03 = 2;
    } else if ((g_InputPressed & g_InputMasks[FISHING_INPUT_CANCEL]) != 0 && D_80144125 == 0) {
        state                = FISHING_STATE;
        D_801440B1           = 0;
        state->mode_index_02 = 1;

        next               = FISHING_STATE;
        next->sub_index_03 = 0;
    }
    Actor_StepAnimLoop();
}

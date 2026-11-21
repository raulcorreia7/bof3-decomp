#include "area030_04.h"

/* Reacts to the confirm/cancel pad bits for the AREA030 prompt: the
 * confirm path clears the pending flag, queues SE 0x200, raises both sprite
 * bytes, retires the panel and steps the work state to 2 with the probe height
 * reset; the cancel path clears the sub-state. Both paths then run the shared
 * per-frame tail. */
/* func_801DA638 */
MATCH void Fishing_CastInput(void) {
    FishingState* work;
    FishingState* tail;
    FishingState* state;
    FishingState* next;

    if ((g_PadStates[0].pressed & g_InputMasks[FISHING_INPUT_CAST]) != 0) {
        D_801440C8 = 0;
        SND_PlaySE(EMI_SE_ID(SND_BANK_AREA, 0));
        D_801E31FC = 0xFF;
        D_801E31F8 = 0xFF;
        Script_Request(2);

        work             = FISHING_STATE;
        work->y_38.pos_y = TO_COORD(65);
        work->step_timer = 0;

        tail            = FISHING_STATE;
        tail->sub_index = 2;
    } else if ((g_PadStates[0].pressed & g_InputMasks[FISHING_INPUT_CANCEL]) != 0 && D_80144125 == 0) {
        state             = FISHING_STATE;
        D_801440B1        = 0;
        state->mode_index = 1;

        next            = FISHING_STATE;
        next->sub_index = 0;
    }
    Actor_StepAnimLoop();
}

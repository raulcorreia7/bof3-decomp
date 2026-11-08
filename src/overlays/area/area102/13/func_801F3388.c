#include "area102_13.h"

MATCH void func_801F3388(void) {
    if (g_GameStateIndex == GAME_REQUEST_IDLE) {
        (g_Task)->timer -= 1;
        if ((g_Task)->timer == 0) {
            (g_Task)->header.step += 1;
            if (func_801F3194() != 0) {
                SND_PlayCue(EMI_CUE_ID(SND_BANK_AREA, 0x00));
            }
        }
    }
}

#include "area102_13.h"

MATCH void func_801F3388(void) {
    if (g_GameStateIndex == GAME_REQUEST_IDLE) {
        ((Actor*)g_Task)->timer -= 1;
        if (((Actor*)g_Task)->timer == 0) {
            ((Actor*)g_Task)->header.step += 1;
            if (func_801F3194() != 0) {
                SND_PlayCue(EMI_CUE_ID(SND_BANK_AREA, 0x00));
            }
        }
    }
}

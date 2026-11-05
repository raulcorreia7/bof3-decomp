#include "area107_13.h"

MATCH void func_801F2DFC(void) {
    if (g_GameStateIndex != GAME_REQUEST_MESSAGE) {
        Game_ClearScriptActive();
        SND_PlayCue(EMI_CUE_ID(2, 6));
        TASK_BYTES[1] = 0;
    }
}

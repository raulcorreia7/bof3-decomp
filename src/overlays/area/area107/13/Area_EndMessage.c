#include "area107_13.h"
#include "area/spad.h"

/* func_801F2DFC */
MATCH void Area_EndMessage(void) {
    if (g_GameStateIndex != GAME_REQUEST_MESSAGE) {
        Game_ClearScriptActive();
        SND_PlayCue(EMI_CUE_ID(SND_BANK_AREA, 6));
        g_Task->header.mode = 0;
    }
}

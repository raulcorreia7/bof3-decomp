#include "area107_13.h"

/* func_801F2DFC */
MATCH void Area_EndMessage(void) {
    if (g_GameStateIndex != GAME_REQUEST_MESSAGE) {
        Game_ClearScriptActive();
        SND_SEPlay(EMI_SE_ID(SND_BANK_AREA, 6));
        SELF(Actor)->header.mode = 0;
    }
}

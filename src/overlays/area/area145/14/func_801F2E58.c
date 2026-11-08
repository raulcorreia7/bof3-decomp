#include "area145_14.h"

MATCH void func_801F2E58(void) {
    if (g_GameStateIndex == GAME_REQUEST_AREA_CHANGE) {
        SND_PlayCue(EMI_CUE_ID(SND_BANK_AREA, 9));
    }
}

#include "area165_13.h"

MATCH void func_801F3518(void) {
    u16 screen_y;

    screen_y           = g_SpadWork->unk_30 - 0x10;
    g_SpadWork->unk_30 = screen_y;
    if ((screen_y << 0x10) <= 0) {
        if (g_GameStateIndex == GAME_REQUEST_IDLE) {
            SND_PlayCue(EMI_CUE_ID(2, 1));
        }
        g_SpadWork->state_02 += 1;
    }
    Area_Update();
}

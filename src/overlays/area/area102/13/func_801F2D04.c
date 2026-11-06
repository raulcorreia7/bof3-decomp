#include "area102_13.h"

MATCH void func_801F2D04(void) {
    if (g_GameStateIndex == GAME_REQUEST_IDLE) {
        ((Actor*)g_Task)->unk_09 -= 1;
        if (((Actor*)g_Task)->unk_09 == 0) {
            ((Actor*)g_Task)->header.step += 1;
            if (func_801F3194() != 0) {
                SND_PlayCue(0x200U);
            }
        }
    }
}

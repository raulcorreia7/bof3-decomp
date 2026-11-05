#include "area075_13.h"

MATCH void func_801F36DC(void) {
    if (g_GameStateIndex == GAME_REQUEST_AREA_CHANGE) {
        SND_PlayCue(0x207);
    } else {
        g_Task->y.fixed = g_AreaScrollTargetY;
        g_ScriptState->cursor -= 2;
    }
}

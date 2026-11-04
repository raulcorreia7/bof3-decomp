#include "area075_13.h"

MATCH void func_801F36DC(void) {
    if (g_GameStateIndex == 5) {
        SND_PlayCue(0x207);
    } else {
        g_SpadWork->y.fixed = g_AreaScrollTargetY;
        g_ScriptState->cursor -= 2;
    }
}

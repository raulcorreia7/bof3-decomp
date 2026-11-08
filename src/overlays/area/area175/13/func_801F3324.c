#include "area175_13.h"

MATCH void func_801F3324(void) {
    if (g_GameStateIndex != GAME_REQUEST_MESSAGE) {
        g_Task->timer       = 16;
        g_Task->header.mode = 3;
    }
    Area_DrawScreenTint();
}

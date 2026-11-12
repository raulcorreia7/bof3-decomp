#include "area175_13.h"

MATCH void func_801F3264(void) {
    g_Task->timer -= 1;
    if (g_Task->timer != 0) {
        g_Task->tint.bytes.unk_5D += 6;
        g_Task->tint.bytes.unk_5E += 6;
        g_Task->tint.bytes.unk_5F += 6;
    } else {
        Message_StartAreaMessage(31);
        g_GameStateIndex    = GAME_REQUEST_MESSAGE;
        g_Task->header.mode = 2;
    }
    Area_DrawScreenTint();
}

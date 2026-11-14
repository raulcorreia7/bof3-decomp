#include "area191_13.h"

MATCH void func_801F2D00(void) {
    u8 mode;

    mode          = g_Task->timer - 1;
    g_Task->timer = mode;
    if (mode & BYTE_MASK) {
        g_Task->tint.bytes.rgb.red += 1;
        g_Task->tint.bytes.rgb.green += 1;
        g_Task->tint.bytes.rgb.blue += 1;
    } else {
        Message_StartAreaMessage(134);
        g_GameStateIndex    = GAME_REQUEST_MESSAGE;
        g_Task->header.mode = 2;
    }
    Area_DrawScreenTint();
}

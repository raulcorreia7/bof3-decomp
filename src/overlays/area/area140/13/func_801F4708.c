#include "area140_13.h"

MATCH void func_801F4708(void) {
    u8* work;

    work = (u8*)g_Task;
    work[9]--;
    if (work[9] == 0) {
        g_Task->mode = 2;
    }
    if (g_GameStateIndex == GAME_REQUEST_AREA_CHANGE) {
        g_Task->mode = 2;
    }
}

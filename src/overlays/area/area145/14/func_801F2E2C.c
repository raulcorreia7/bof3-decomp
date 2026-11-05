#include "area145_14.h"

MATCH void func_801F2E2C(void) {
    if (g_GameStateIndex != GAME_REQUEST_AREA_CHANGE) {
        g_Task->step = 1;
    }
}

#include "area051_13.h"

MATCH void func_801F2C04(void) {
    u8 code;

    code = func_801BE0C0(g_Task->x.fixed, g_Task->y.fixed, g_Task->state_70.word);
    if (code != 0xFF && !(g_AreaWalkFlags & 0x1000) && g_GameStateIndex == GAME_REQUEST_IDLE) {
        func_8015C214(code, 1);
    }
}

#include "area051_13.h"

MATCH void func_801F2C04(void) {
    u8 code;

    code = func_801BE0C0(g_SpadWork->x.fixed, g_SpadWork->y.fixed, g_SpadWork->state_70.word);
    if (code != 0xFF && !(g_AreaWalkFlags & 0x1000) && g_GameStateIndex == 0) {
        func_8015C214(code, 1);
    }
}

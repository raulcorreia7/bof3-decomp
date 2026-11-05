#include "area104_14.h"

MATCH s32 func_801F5140(void) {
    if (g_InputHeld & 0x4000) {
        g_SpadWork->direction_08 ^= 4;
    } else if (g_InputHeld & 0x2000) {
        g_SpadWork->direction_08++;
    } else if (g_InputHeld & 0x8000) {
        g_SpadWork->direction_08--;
    } else if (!(g_InputHeld & 0x1000)) {
        return 0;
    }
    g_SpadWork->direction_08 &= 7;
    return 1;
}

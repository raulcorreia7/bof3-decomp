#include "battle_03.h"

MATCH void func_801E1D88(void) {
    if ((func_801DEE4C() & 0xFF) != 0u) {
        g_Task->header.mode = 8u;
        g_Task->header.step = 0u;
    }
}

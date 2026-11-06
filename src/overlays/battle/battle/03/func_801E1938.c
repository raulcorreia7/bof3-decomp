#include "battle_03.h"

MATCH void func_801E1938(void) {
    if (func_801DEE4C() != 0u) {
        g_Task->header.mode = (g_Task->header.mode + 1u);
        g_Task->header.step = 0u;
    }
}

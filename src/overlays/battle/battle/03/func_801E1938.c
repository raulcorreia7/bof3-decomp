#include "battle_03.h"

MATCH void func_801E1938(void) {
    if (func_801DEE4C() != 0u) {
        g_Task->mode = (u8)(g_Task->mode + 1u);
        g_Task->step = 0u;
    }
}

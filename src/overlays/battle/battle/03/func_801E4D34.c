#include "battle_03.h"

MATCH void func_801E4D34(void) {
    if (func_801E3160() != 0u) {
        g_Task->mode = (g_Task->mode + 1u);
        g_Task->step = 0u;
    }
}

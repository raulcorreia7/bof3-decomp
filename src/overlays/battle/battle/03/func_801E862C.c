#include "battle_03.h"

MATCH void func_801E862C(void) {
    Callback table[2] = {func_801E8684, func_801E8D04};

    table[g_Task->header.mode]();
}

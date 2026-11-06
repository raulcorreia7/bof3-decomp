#include "battle_03.h"

MATCH void func_801E72A8(void) {
    Callback handlers[2];

    handlers[0] = func_801E72F4;
    handlers[g_Task->header.mode]();
}

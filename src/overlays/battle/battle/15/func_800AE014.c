#include "battle_15.h"
#include "area/spad.h"

MATCH void func_800AE014(void) {
    Callback handlers[2] = {func_800AE06C, func_800AE09C};

    handlers[g_Task->header.mode]();
}

#include "battle_15.h"
#include "area/spad.h"

MATCH void func_800A83F8(void) {
    Callback handlers[2] = {func_800A8450, func_800A84FC};

    handlers[g_Task->header.mode]();
}

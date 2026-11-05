#include "battle_15.h"

MATCH void func_800A83F8(void) {
    Callback handlers[2] = {func_800A8450, func_800A84FC};

    handlers[TASK_BYTES[1]]();
}

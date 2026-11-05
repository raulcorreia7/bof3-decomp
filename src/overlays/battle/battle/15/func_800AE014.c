#include "battle_15.h"

MATCH void func_800AE014(void) {
    Callback handlers[2] = {func_800AE06C, func_800AE09C};

    handlers[TASK_BYTES[1]]();
}

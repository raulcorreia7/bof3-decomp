#include "game_00.h"

MATCH void func_801B3540(void) {
    u8*      work    = TASK_BYTES;
    Callback handler = D_801CD154[work[3]];
    handler();
}

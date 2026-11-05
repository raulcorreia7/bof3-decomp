#include "game_00.h"

MATCH void func_801ACBC4(void) {
    u8*      work    = TASK_BYTES;
    Callback handler = D_801C8904[work[4]];
    handler();
}

#include "game_00.h"

MATCH void func_801B3260(void) {
    u8*      work    = TASK_BYTES;
    Callback handler = D_801CD130[work[2]];
    handler();
}

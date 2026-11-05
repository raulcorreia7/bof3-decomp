#include "game_00.h"

MATCH void func_801B790C(void) {
    u8*      work    = TASK_BYTES;
    Callback handler = D_801CD310[work[4]];
    handler();
}

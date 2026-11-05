#include "game_00.h"

MATCH void func_801B371C(void) {
    u8*      work    = TASK_BYTES;
    Callback handler = D_801CD1B0[work[2]];

    handler();
    func_8014D978();
}

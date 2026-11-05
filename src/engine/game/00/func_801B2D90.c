#include "game_00.h"

MATCH void func_801B2D90(void) {
    u8*      work    = TASK_BYTES;
    Callback handler = D_801CD120[work[2]];

    handler();
    func_8014D978();
}

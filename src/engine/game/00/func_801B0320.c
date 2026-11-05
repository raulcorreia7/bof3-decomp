#include "game_00.h"

MATCH void func_801B0320(void) {
    u8*      work    = TASK_BYTES;
    Callback handler = D_801CD0E8[work[2]];
    handler();
    func_8014D978();
}

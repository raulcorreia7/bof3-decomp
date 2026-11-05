#include "game_00.h"

MATCH void func_801BBFB4(void) {
    u8*      work    = TASK_BYTES;
    Callback handler = D_801CD440[work[2]];
    handler();
    func_8014D978();
}

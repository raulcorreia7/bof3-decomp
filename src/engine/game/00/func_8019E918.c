#include "game_00.h"

MATCH void func_8019E918(void) {
    u8*      work    = TASK_BYTES;
    Callback handler = D_801C81B8[work[2]];
    handler();
}

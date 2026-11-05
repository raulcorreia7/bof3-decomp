#include "game_00.h"

/* Plain scratchpad cell read; emits a fresh absolute load per use. */
#define WORK_PTR (*SP_PTR(Actor*, 0x44u))

MATCH void func_8019E424(void) {
    D_801C81A0[WORK_PTR->step]();
}

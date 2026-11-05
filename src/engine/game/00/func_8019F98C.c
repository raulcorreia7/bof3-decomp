#include "game_00.h"

/* Plain scratchpad cell read; emits a fresh absolute load per use. */
#define WORK_PTR (*SP_PTR(Actor*, 0x44u))

MATCH void func_8019F98C(void) {
    D_801C81DC[WORK_PTR->mode]();
}

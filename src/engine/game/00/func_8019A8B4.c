#include "game_00.h"

/* Plain scratchpad cell read; emits a fresh absolute load per use. */
#define WORK_PTR (*SP_PTR(Actor*, 0x44u))

MATCH void func_8019A8B4(void) {
    D_801C80E0[WORK_PTR->unk_01]();
    g_AreaCameraRefreshCount = 2;
}

/* The dispatch dance keeps every work-cell write. */
#define FAKE_DECL_TASK_VOLATILE
#include "area134_13.h"

#ifdef NON_MATCHING
NON_MATCHING void func_801F35D4(void) {
    Actor* work;
    s32    state;

    work        = g_Task;
    g_Task      = g_Actors;
    g_GameState = g_Game.members;
    g_Task      = work;
    TASK_SET(g_Game.members);
    g_Task = work;
    if (FIELD(s32, D_801468BC, 0) >= D_80145EC4) {
        work->header.mode = 0x16;
    }
    if (D_80146866 == 0x80) {
        g_Task->header.mode = 0x17;
    }
    state = D_80146865;
    if (state == 4) {
        g_Task->header.mode = 4;
    } else if (state < 5) {
        if (state == 3) {
            g_Task->header.mode = 6;
        }
    } else if (state == 5) {
        g_Task->header.mode = 2;
    } else if (state == 0xFF) {
        func_80196070();
    }
}
#else
INCLUDE_ASM(func_801F35D4);
#endif

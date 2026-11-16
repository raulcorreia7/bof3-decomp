#define FAKE_DECL_TASK_VOLATILE
#include "area134_13.h"

#ifdef NON_MATCHING
NON_MATCHING void func_801F2C78(void) {
    Actor* work;

    work        = g_Task;
    g_Task      = g_Actors;
    g_GameState = g_Game.members;
    g_Task      = work;
    TASK_SET(g_Game.members);
    g_Task = work;
    if (FIELD(s32, D_801468BC, 0) >= g_Game.members[0].pos.x.fixed) {
        work->header.mode = 0x16;
    }
    if (D_80146866 == 0x80) {
        g_Task->header.mode = 0x17;
    }
    if (D_80146865 == 4) {
        g_Task->header.mode = 4;
    } else if (D_80146865 < 5) {
        if (D_80146865 == 3) {
            g_Task->header.mode = 6;
        }
    } else if (D_80146865 == 5) {
        g_Task->header.mode = 2;
    } else if (D_80146865 == 0xFF) {
        func_80196070();
    }
}
#else
INCLUDE_ASM(func_801F2C78);
#endif

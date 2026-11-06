#include "area112_13.h"

MATCH void func_801F2E14(void) {
    if (!SYS_TestFlag(g_SceneEventFlags, COORD_FRAC(g_Task->pos.x))) {
        g_Task->unk_09 = 0;
        g_Task->header.step++;
        COORD_INT(g_Task->pos.y) = 8;
        func_801F2EA8();
        SND_PlayCue(0x202);
        SND_PlayCue(0x201);
    }
    func_801F3274();
}

#include "area042_13.h"

MATCH void func_801F3A0C(void) {
    if (SYS_TestFlag(g_SceneEventFlags, D_801F532C[COORD_INT(g_Task->pos.x)]) != 0) {
        SND_PlayCue(0x201U);
        g_Task->unk_09 = 0;
        g_Task->header.step += 1;
    }
}

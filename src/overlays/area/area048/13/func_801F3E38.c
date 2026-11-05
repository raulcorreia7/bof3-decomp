#include "area048_13.h"

MATCH void func_801F3E38(void) {
    if (((g_Task->x.part.integer == 0) && (SYS_TestFlag(g_SceneEventFlags, 0xD) != 0)) ||
        ((g_Task->x.part.integer != 0) && (D_8014686B != 0))) {
        SND_PlayCue(0x20DU);
        g_Task->unk_09 = 0;
        g_Task->step += 1;
    }
}

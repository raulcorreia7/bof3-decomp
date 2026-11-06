#include "area048_13.h"

MATCH void func_801F3E38(void) {
    if (((COORD_INT(g_Task->pos.x) == 0) && (SYS_TestFlag(g_SceneEventFlags, 0xD) != 0)) ||
        ((COORD_INT(g_Task->pos.x) != 0) && (D_8014686B != 0))) {
        SND_PlayCue(0x20DU);
        g_Task->unk_09 = 0;
        g_Task->header.step += 1;
    }
}

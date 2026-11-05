#include "area086_13.h"
#include "work/area_spad.h"

MATCH void func_801F2CAC(void) {
    if (SYS_TestFlag(g_SceneEventFlags, g_Task->x.part.fraction) != 0) {
        g_Task->unk_09 = 0;
        g_Task->step++;
        SND_PlayCue(0x202);
        SND_PlayCue(0x201);
    }
    func_801F3070();
}

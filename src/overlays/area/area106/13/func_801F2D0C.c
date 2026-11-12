#include "area106_13.h"

MATCH void func_801F2D0C(void) {
    func_801F2F38(g_Task->timer >= 12, D_801F3E90[g_Task->timer] << 4);
    g_Task->timer += 1;
    if (g_Task->timer >= 16U) {
        if (SYS_TestFlag(g_SceneEventFlags, 79) != 0) {
            SND_PlayCue(0x200);
        } else {
            SND_PlayCue(0x201);
        }
        g_Task->unk_0A = 0;
        g_Task->header.step += 1;
    }
}

#include "area106_13.h"

MATCH void func_801F2D0C(void) {
    func_801F2F38(TASK(Actor)->timer >= 12, D_801F3E90[TASK(Actor)->timer] << 4);
    TASK(Actor)->timer += 1;
    if (TASK(Actor)->timer >= 16U) {
        if (SYS_TestFlag(g_SceneEventFlags, 79) != 0) {
            SND_SEPlay(0x200);
        } else {
            SND_SEPlay(0x201);
        }
        TASK(Actor)->unk_0A = 0;
        TASK(Actor)->header.step += 1;
    }
}

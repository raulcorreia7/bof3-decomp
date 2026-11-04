#include "area112_13.h"

MATCH void func_801F2D18(void) {
    if (SYS_TestFlag(g_SceneEventFlags, g_SpadWork->x.part.fraction)) {
        g_SpadWork->unk_09     = 0;
        g_SpadWork->state_02   = 1;
        g_SpadWork->y.part.integer = -8;
        func_801F2EA8();
        SND_PlayCue(0x202);
        SND_PlayCue(0x201);
    }
    func_801F3274();
}

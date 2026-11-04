#include "area042_13.h"

MATCH void func_801F3A0C(void) {
    if (SYS_TestFlag(g_SceneEventFlags, D_801F532C[g_SpadWork->x.part.integer]) != 0) {
        SND_PlayCue(0x201U);
        g_SpadWork->unk_09 = 0;
        g_SpadWork->state_02 += 1;
    }
}

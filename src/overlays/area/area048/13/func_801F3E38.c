#include "area048_13.h"

MATCH void func_801F3E38(void) {
    if (((((Actor*)g_SpadWork)->x.part.integer == 0) && (SYS_TestFlag(g_SceneEventFlags, 0xD) != 0)) ||
        ((((Actor*)g_SpadWork)->x.part.integer != 0) && (D_8014686B != 0))) {
        SND_PlayCue(0x20DU);
        ((Actor*)g_SpadWork)->unk_09 = 0;
        ((Actor*)g_SpadWork)->state_02 += 1;
    }
}

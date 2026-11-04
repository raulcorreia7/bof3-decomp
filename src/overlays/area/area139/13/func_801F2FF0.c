#include "area139_13.h"

MATCH void func_801F2FF0(void) {
    if (D_80143F03 == 2 && !SYS_TestFlag(g_SceneEventFlags, 0x5C)) {
        SND_PlayCue(0x206);
        g_SpadWork->unk_01 = 0;
    }
    if (D_80143F03 == 3 && SYS_TestFlag(g_SceneEventFlags, 0x5D)) {
        SND_PlayCue(0x206);
        g_SpadWork->unk_01 = 0;
    }
}

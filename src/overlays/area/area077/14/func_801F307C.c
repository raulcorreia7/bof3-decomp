#include "area077_14.h"

MATCH void func_801F307C(void) {
    if (SYS_TestFlag(g_SceneFlags, 0x25)) {
        if (SYS_TestFlag(g_SceneFlags, 0x26)) {
            SND_PlayCue(0x206);
        } else {
            SND_PlayCue(0x204);
        }
    }
    SYS_ClearFlag(g_SceneFlags, 0x2D);
    Actor_Clear();
}

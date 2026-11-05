#include "area148_13.h"

MATCH void func_801F36A0(void) {
    if (SYS_TestFlag(g_SceneEventFlags, 0x5A) != 0) {
        if (g_GameStateIndex == 0) {
            SND_PlayCue(0x208U);
        }
        ((Actor*)g_SpadWork)->state_02 += 1;
    }
    func_801F37B8(0, 1);
    func_801F37B8(1, 1);
}

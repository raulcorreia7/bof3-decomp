#include "area102_13.h"

MATCH void func_801F3388(void) {
    if (g_GameStateIndex == 0) {
        ((Actor*)g_SpadWork)->unk_09 -= 1;
        if (((Actor*)g_SpadWork)->unk_09 == 0) {
            ((Actor*)g_SpadWork)->state_02 += 1;
            if (func_801F3194() != 0) {
                SND_PlayCue(0x200U);
            }
        }
    }
}

#include "area117_13.h"

MATCH void func_801F3024(void) {
    u16 position;

    position           = g_SpadWork->unk_30 + 0x20;
    g_SpadWork->unk_30 = position;
    if ((s16)position >= 0) {
        func_801F2E08();
        if (g_SpadWork->state_02 == 2) {
            return;
        }
        g_SpadWork->state_02 = 1;
        if (g_GameStateIndex == 0) {
            SND_PlayCue(0x201);
        }
    }
    func_801F314C();
}

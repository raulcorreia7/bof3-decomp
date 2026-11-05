#include "area118_13.h"

MATCH void func_801F36B4(void) {
    u16 count;

    count              = g_SpadWork->unk_30 + 0x20;
    g_SpadWork->unk_30 = count;
    if ((s16)count >= 0) {
        func_801F33A4();
        if (g_SpadWork->state_02 == 2) {
            return;
        }
        if (g_GameStateIndex == 0) {
            SND_PlayCue(0x201);
        }
        g_SpadWork->state_02 = 1;
    }
    func_801F381C(0);
}

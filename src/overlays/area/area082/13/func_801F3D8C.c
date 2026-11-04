#include "area082_13.h"

MATCH void func_801F3D8C(void) {
    g_SpadWork->unk_09++;
    if (g_SpadWork->unk_09 >= 0x11) {
        g_SpadWork->unk_09 = 0;
        SND_PlayCue(0x201U);
        g_SpadWork->state_02++;
    }
    func_801F4430();
}

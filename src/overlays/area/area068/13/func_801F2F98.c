#include "area068_13.h"

MATCH void func_801F2F98(void) {
    if (--D_801F4DFC == 0) {
        SND_PlayCue(0x201);
        D_801F4DFC         = 0;
        D_801F4E08         = D_801F4E04;
        g_SpadWork->unk_01 = 0xA;
    } else if (g_InputPressed == 0x10) {
        D_801F4E0C = 0;
        D_801F4E04 += 1;
        g_SpadWork->unk_01 = 1;
    } else {
        g_SpadWork->unk_01 = 3;
    }
}

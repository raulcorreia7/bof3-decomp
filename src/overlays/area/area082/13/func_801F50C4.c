#include "area082_13.h"

MATCH void func_801F50C4(void) {
    D_8014933A = 0;
    func_801F5428(-1);
    SND_PlayCue(0x202);
    SND_PlayCue(0x200);
    g_Task->unk_09 = 0;
    g_Task->header.step++;
}

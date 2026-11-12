#include "boss008_16.h"

MATCH void func_800C1AB4(void) {
    PartyMember* work;
    PartyMember* spad;

    func_800C236C(g_Task->unk_09);
    work = g_Task;
    if (work->unk_09 == 0x30) {
        work->unk_48  = 2;
        spad          = g_Task;
        spad->scale.x = ONE;
        spad->scale.y = ONE;
        SND_PlayCue(EMI_CUE_ID(SND_BANK_ENEMY, 2));
        g_Task->unk_04++;
    } else {
        work->unk_09 += 4;
    }
}

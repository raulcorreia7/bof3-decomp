#include "boss008_16.h"

MATCH void func_800C1AB4(void) {
    PartyBattler* work;
    PartyBattler* spad;

    func_800C236C(g_SpadWork->word_08.byte.unk_09);
    work = g_SpadWork;
    if (work->word_08.byte.unk_09 == 0x30) {
        work->unk_48 = 2;
        spad         = g_SpadWork;
        spad->unk_40 = 0x10000;
        spad->unk_44 = 0x10000;
        SND_PlayCue(EMI_CUE_ID(6, 2));
        g_SpadWork->unk_04++;
    } else {
        work->word_08.byte.unk_09 += 4;
    }
}

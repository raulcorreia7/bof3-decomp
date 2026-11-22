#include "boss008_16.h"

MATCH void func_800C1AB4(void) {
    PartyMember* work;
    PartyMember* spad;

    func_800C236C(TASK(PartyMember)->unk_09);
    work = TASK(PartyMember);
    if (work->unk_09 == 0x30) {
        work->unk_48  = 2;
        spad          = TASK(PartyMember);
        spad->scale.x = 0x10000;
        spad->scale.y = 0x10000;
        SND_SEPlay(EMI_SE_ID(SND_BANK_ENEMY, 2));
        TASK(PartyMember)->unk_04++;
    } else {
        work->unk_09 += 4;
    }
}

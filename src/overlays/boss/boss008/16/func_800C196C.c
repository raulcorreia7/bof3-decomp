#include "boss008_16.h"

MATCH void func_800C196C(void) {
    TASK(PartyMember)->unk_09 = 0x40;
    TASK(PartyMember)->timer  = 64;
    SND_SEPlay(EMI_SE_ID(SND_BANK_ENEMY, 1));
    TASK(PartyMember)->unk_04++;
}

#include "boss008_16.h"

MATCH void func_800C196C(void) {
    SELF(PartyMember)->unk_09 = 0x40;
    SELF(PartyMember)->timer  = 64;
    SND_SEPlay(EMI_SE_ID(SND_BANK_ENEMY, 1));
    SELF(PartyMember)->unk_04++;
}

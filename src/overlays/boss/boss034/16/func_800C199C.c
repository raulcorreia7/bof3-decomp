#include "boss034_16.h"

MATCH void func_800C199C(void) {
    u8* flags;
    u8  timer;

    timer = SELF(PartyMember)->unk_09;
    if (timer == SELF(PartyMember)->timer) {
        flags = &g_Battle.boss_flags;
        if (!(*flags & 0x4)) {
            SND_SEPlay(EMI_SE_ID(SND_BANK_ENEMY, 1));
            *flags |= 4;
        }
        func_801D9DBC(0, 0, 11, 65535, 1);
        SELF(PartyMember)->timer = SELF(PartyMember)->timer >> 1;
    } else {
        SELF(PartyMember)->unk_09 = timer - 1;
    }
    if (SELF(PartyMember)->unk_09 == 0) {
        SELF(PartyMember)->unk_03 += 1;
    }
}

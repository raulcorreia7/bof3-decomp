#include "boss034_16.h"

MATCH void func_800C199C(void) {
    u8* flags;
    u8  timer;

    timer = ((PartyMember*)g_Task)->unk_09;
    if (timer == ((PartyMember*)g_Task)->timer) {
        flags = &g_Battle.boss_flags;
        if (!(*flags & 0x4)) {
            SND_PlayCue(EMI_CUE_ID(SND_BANK_ENEMY, 1));
            *flags |= 4;
        }
        func_801D9DBC(0, 0, 11, 65535, 1);
        ((PartyMember*)g_Task)->timer = ((PartyMember*)g_Task)->timer >> 1;
    } else {
        ((PartyMember*)g_Task)->unk_09 = timer - 1;
    }
    if (((PartyMember*)g_Task)->unk_09 == 0) {
        ((PartyMember*)g_Task)->unk_03 += 1;
    }
}

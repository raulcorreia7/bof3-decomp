#include "boss034_16.h"

MATCH void func_800C199C(void) {
    u8* flags;
    u8  timer;

    timer = ((PartyBattler*)g_SpadWork)->word_08.byte.unk_09;
    if (timer == ((PartyBattler*)g_SpadWork)->word_08.byte.unk_0A) {
        flags = &g_BattleBossFlags;
        if (!(*flags & 4)) {
            SND_PlayCue(0x601U);
            *flags |= 4;
        }
        func_801D9DBC(0, 0, 0xB, 0xFFFF, 1);
        ((PartyBattler*)g_SpadWork)->word_08.byte.unk_0A = ((PartyBattler*)g_SpadWork)->word_08.byte.unk_0A >> 1;
    } else {
        ((PartyBattler*)g_SpadWork)->word_08.byte.unk_09 = timer - 1;
    }
    if (((PartyBattler*)g_SpadWork)->word_08.byte.unk_09 == 0) {
        ((PartyBattler*)g_SpadWork)->unk_03 += 1;
    }
}

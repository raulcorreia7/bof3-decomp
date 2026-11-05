#include "boss055_16.h"

MATCH void func_800C1FBC(void) {
    u8 count;

    ((PartyBattler*)g_SpadWork)->word_08.byte.unk_0B = 0;
    count                                            = ((PartyBattler*)g_SpadWork)->word_08.byte.unk_09;
    if (count == 0) {
        if ((D_801463BE == 3) || (D_801463BE == 5)) {
            SND_PlayCue(0x602U);
        }
        ((PartyBattler*)g_SpadWork)->unk_02 += 1;
    } else {
        ((PartyBattler*)g_SpadWork)->word_08.byte.unk_09 = count - 1;
    }
    func_801E3160();
}

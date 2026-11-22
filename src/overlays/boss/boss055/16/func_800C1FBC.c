#include "boss055_16.h"

MATCH void func_800C1FBC(void) {
    u8 count;

    ((PartyMember*)g_Task)->param.unk_0B = 0;
    count                                = ((PartyMember*)g_Task)->unk_09;
    if (count == 0) {
        if ((g_Battle.unk_DE == 3) || (g_Battle.unk_DE == 5)) {
            SND_SEPlay(0x602U);
        }
        ((PartyMember*)g_Task)->header.step += 1;
    } else {
        ((PartyMember*)g_Task)->unk_09 = count - 1;
    }
    func_801E3160();
}

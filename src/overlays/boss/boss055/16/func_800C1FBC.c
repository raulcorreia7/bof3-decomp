#include "boss055_16.h"

MATCH void func_800C1FBC(void) {
    u8 count;

    SELF(PartyMember)->param.unk_0B = 0;
    count                           = SELF(PartyMember)->unk_09;
    if (count == 0) {
        if ((g_Battle.unk_DE == 3) || (g_Battle.unk_DE == 5)) {
            SND_SEPlay(0x602U);
        }
        SELF(PartyMember)->header.step += 1;
    } else {
        SELF(PartyMember)->unk_09 = count - 1;
    }
    func_801E3160();
}

#include "boss034_16.h"

MATCH void func_800C1B40(void) {
    TASK(PartyMember)->unk_20 += TASK(PartyMember)->timer;
    if (TASK(PartyMember)->unk_0C > 40) {
        TASK(PartyMember)->unk_0C--;
        if (g_FrameCount & 1) {
            TASK(PartyMember)->unk_1C++;
        }
    }
    if (TASK(PartyMember)->unk_10 > 40) {
        TASK(PartyMember)->unk_10 -= 1;
    }
    func_800C23D4((u16)TASK(PartyMember)->unk_20);
    if (g_FrameCount & 7) {
        TASK(PartyMember)->timer++;
    }
    if (TASK(PartyMember)->timer >= 64) {
        TASK(PartyMember)->unk_03++;
    }
}

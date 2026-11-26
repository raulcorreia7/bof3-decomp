#include "boss034_16.h"

MATCH void func_800C1B40(void) {
    SELF(PartyMember)->unk_20 += SELF(PartyMember)->timer;
    if (SELF(PartyMember)->unk_0C > 40) {
        SELF(PartyMember)->unk_0C--;
        if (g_FrameCount & 1) {
            SELF(PartyMember)->unk_1C++;
        }
    }
    if (SELF(PartyMember)->unk_10 > 40) {
        SELF(PartyMember)->unk_10 -= 1;
    }
    func_800C23D4((u16)SELF(PartyMember)->unk_20);
    if (g_FrameCount & 7) {
        SELF(PartyMember)->timer++;
    }
    if (SELF(PartyMember)->timer >= 64) {
        SELF(PartyMember)->unk_03++;
    }
}

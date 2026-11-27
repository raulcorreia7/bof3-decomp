#include "boss055_16.h"

MATCH void func_800C19FC(void) {
    SELF(PartyMember)->param.unk_0B = 0;
    func_801E30F8();
    SELF(PartyMember)->header.mode++;
    SELF(PartyMember)->header.step = 0;
}

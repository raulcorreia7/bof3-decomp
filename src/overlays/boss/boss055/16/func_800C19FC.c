#include "boss055_16.h"

MATCH void func_800C19FC(void) {
    TASK(PartyMember)->param.unk_0B = 0;
    func_801E30F8();
    TASK(PartyMember)->header.mode++;
    TASK(PartyMember)->header.step = 0;
}

#include "boss034_16.h"

MATCH void func_800C1940(void) {
    if (Script_AnimStepLoop() != 0) {
        SELF(PartyMember)->unk_09 = 64;
        SELF(PartyMember)->timer  = 32;
        SELF(PartyMember)->unk_03 = 1;
    }
}

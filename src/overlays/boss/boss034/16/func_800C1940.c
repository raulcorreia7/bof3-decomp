#include "boss034_16.h"

MATCH void func_800C1940(void) {
    if (Script_AnimStepLoop() != 0) {
        TASK(PartyMember)->unk_09 = 64;
        TASK(PartyMember)->timer  = 32;
        TASK(PartyMember)->unk_03 = 1;
    }
}

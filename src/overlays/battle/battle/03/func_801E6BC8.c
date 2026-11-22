#include "battle_03.h"

MATCH void func_801E6BC8(void) {
    if (Script_AnimStepLoop() != 0u) {
        TASK(PartyMember)->header.mode++;
        TASK(PartyMember)->unk_09 = 0x10;
    }
}

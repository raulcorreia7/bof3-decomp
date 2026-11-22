#include "battle_15.h"

MATCH void func_800A8CC8(void) {
    Script_Select((TASK(PartyMember)->facing + 0x50) & BYTE_MASK);
    func_801DEE4C();
    TASK(PartyMember)->unk_29 = 3;
    TASK(PartyMember)->unk_09 = 8;
    TASK(PartyMember)->header.mode++;
}

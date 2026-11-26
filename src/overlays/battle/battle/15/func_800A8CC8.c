#include "battle_15.h"

MATCH void func_800A8CC8(void) {
    Script_Select((SELF(PartyMember)->facing + 0x50) & BYTE_MASK);
    func_801DEE4C();
    SELF(PartyMember)->unk_29 = 3;
    SELF(PartyMember)->unk_09 = 8;
    SELF(PartyMember)->header.mode++;
}

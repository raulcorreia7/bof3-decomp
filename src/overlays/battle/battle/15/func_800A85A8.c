#include "battle_15.h"

MATCH void func_800A85A8(void) {
    PartyMember* work;

    work         = SELF(PartyMember);
    work->unk_20 = work->pos.z.fixed + 0x04000000;
    Script_Select((work->facing + 0x38) & BYTE_MASK);
    SELF(PartyMember)->param.unk_0B = 0x10;
    SELF(PartyMember)->header.mode++;
}

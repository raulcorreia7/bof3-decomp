#include "boss013_16.h"

MATCH void func_800C1D9C(void) {
    Area_SceneSelectRecord(0xF9);
    SELF(PartyMember)->unk_24 &= 0xFE;
    Script_Select(2);
    SELF(PartyMember)->header.step++;
}

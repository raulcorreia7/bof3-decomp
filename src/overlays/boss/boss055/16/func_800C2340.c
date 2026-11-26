#include "boss055_16.h"

MATCH void func_800C2340(u8 arg0, u8 index, u8 value) {
    func_800C238C(arg0, index);
    SELF(PartyMember)->param.unk_0B = 1;
    g_Battle.unk_DE                 = value;
}

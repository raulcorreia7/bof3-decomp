#include "boss008_16.h"

MATCH void func_800C1B48(void) {
    u32 value;
    u32 value2;
    u8  value3;

    func_800C236C(SELF(PartyMember)->unk_09);
    value3 = SELF(PartyMember)->unk_09;
    if (value3 == 0) {
        SELF(PartyMember)->unk_48 = 0;
        Area_SceneSelectRecord(0x83);
        Script_Select(0U);
        Battle_DefeatEnemy();
        SELF(PartyMember)->header.flags &= ~ACTOR_FLAG_HIDDEN;
        SELF(PartyMember)->header.mode = 6;
        SELF(PartyMember)->header.step = 4;
        SELF(PartyMember)->unk_03 += 1;
        SELF(PartyMember)->unk_04 = 0;
        return;
    }
    SELF(PartyMember)->unk_09 = value3 - 4;
    value                     = SELF(PartyMember)->scale.x;
    if ((s32)value > 0) {
        SELF(PartyMember)->scale.x = value - 0x2000;
    } else {
        SELF(PartyMember)->scale.x = 0;
    }
    value2 = SELF(PartyMember)->scale.y;
    if ((s32)value2 > 0) {
        SELF(PartyMember)->scale.y = value2 - 0x2000;
        return;
    }
    SELF(PartyMember)->scale.y = 0;
}

#include "boss008_16.h"

MATCH void func_800C1B48(void) {
    u32 value;
    u32 value2;
    u8  value3;

    func_800C236C(TASK(PartyMember)->unk_09);
    value3 = TASK(PartyMember)->unk_09;
    if (value3 == 0) {
        TASK(PartyMember)->unk_48 = 0;
        Area_SceneSelectRecord(0x83);
        Script_Select(0U);
        Battle_DefeatEnemy();
        TASK(PartyMember)->header.flags &= ~ACTOR_FLAG_HIDDEN;
        TASK(PartyMember)->header.mode = 6;
        TASK(PartyMember)->header.step = 4;
        TASK(PartyMember)->unk_03 += 1;
        TASK(PartyMember)->unk_04 = 0;
        return;
    }
    TASK(PartyMember)->unk_09 = value3 - 4;
    value                     = TASK(PartyMember)->scale.x;
    if ((s32)value > 0) {
        TASK(PartyMember)->scale.x = value - 0x2000;
    } else {
        TASK(PartyMember)->scale.x = 0;
    }
    value2 = TASK(PartyMember)->scale.y;
    if ((s32)value2 > 0) {
        TASK(PartyMember)->scale.y = value2 - 0x2000;
        return;
    }
    TASK(PartyMember)->scale.y = 0;
}

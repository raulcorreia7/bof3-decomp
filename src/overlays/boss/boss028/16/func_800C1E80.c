#include "boss028_16.h"

MATCH void func_800C1E80(void) {
    COORD_INT(TASK(PartyMember)->pos.z) += TASK(PartyMember)->unk_14;
    TASK(PartyMember)->unk_14 += TASK(PartyMember)->unk_20;
    /* FAKE: the s16 return is read as s32; retail adds 0x400 to the raw register. */
    if (COORD_INT(TASK(PartyMember)->pos.z) > ((s32 (*)(s32, s32))Area_HeightSample)(TASK(PartyMember)->pos.x.fixed, TASK(PartyMember)->pos.y.fixed) + 0x400) {
        COORD_INT(TASK(PartyMember)->pos.z) = ((s32 (*)(s32, s32))Area_HeightSample)(TASK(PartyMember)->pos.x.fixed, TASK(PartyMember)->pos.y.fixed) + 0x400;
        TASK(PartyMember)->unk_14           = 0;
        TASK(PartyMember)->unk_20           = -0x40;
        TASK(PartyMember)->header.step--;
    }
}

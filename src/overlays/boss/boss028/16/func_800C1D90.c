#include "boss028_16.h"

MATCH void func_800C1D90(void) {
    COORD_INT(SELF(PartyMember)->pos.z) += SELF(PartyMember)->unk_14;
    SELF(PartyMember)->unk_14 += SELF(PartyMember)->unk_20;
    /* FAKE: the s16 return is read as s32; retail adds 0x200 to the raw register. */
    if (COORD_INT(SELF(PartyMember)->pos.z) < ((s32 (*)(s32, s32))Area_HeightSample)(SELF(PartyMember)->pos.x.fixed, SELF(PartyMember)->pos.y.fixed) + 0x200) {
        COORD_INT(SELF(PartyMember)->pos.z) = ((s32 (*)(s32, s32))Area_HeightSample)(SELF(PartyMember)->pos.x.fixed, SELF(PartyMember)->pos.y.fixed) + 0x200;
        SELF(PartyMember)->unk_14           = 0;
        SELF(PartyMember)->unk_20           = 0x40;
        SND_SEQueueSelection(0x600);
        if (SELF(PartyMember)->unk_09 != 0) {
            SELF(PartyMember)->unk_09--;
            SELF(PartyMember)->header.step += 1;
        } else {
            SELF(PartyMember)->header.step += 2;
        }
    }
}

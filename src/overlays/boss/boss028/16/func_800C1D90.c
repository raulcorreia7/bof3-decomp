#include "boss028_16.h"

MATCH void func_800C1D90(void) {
    COORD_INT(TASK(PartyMember)->pos.z) += TASK(PartyMember)->unk_14;
    TASK(PartyMember)->unk_14 += TASK(PartyMember)->unk_20;
    /* FAKE: the s16 return is read as s32; retail adds 0x200 to the raw register. */
    if (COORD_INT(TASK(PartyMember)->pos.z) < ((s32 (*)(s32, s32))Area_HeightSample)(TASK(PartyMember)->pos.x.fixed, TASK(PartyMember)->pos.y.fixed) + 0x200) {
        COORD_INT(TASK(PartyMember)->pos.z) = ((s32 (*)(s32, s32))Area_HeightSample)(TASK(PartyMember)->pos.x.fixed, TASK(PartyMember)->pos.y.fixed) + 0x200;
        TASK(PartyMember)->unk_14           = 0;
        TASK(PartyMember)->unk_20           = 0x40;
        SND_SEQueueSelection(0x600);
        if (TASK(PartyMember)->unk_09 != 0) {
            TASK(PartyMember)->unk_09--;
            TASK(PartyMember)->header.step += 1;
        } else {
            TASK(PartyMember)->header.step += 2;
        }
    }
}

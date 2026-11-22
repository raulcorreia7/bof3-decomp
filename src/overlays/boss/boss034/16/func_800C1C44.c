#include "boss034_16.h"

MATCH void func_800C1C44(void) {
    Area_SceneSelectRecord(0x1C1);
    TASK(PartyMember)->unk_2A = 1;
    Script_Select(8U);
    TASK(PartyMember)->unk_24 &= 0x77;
    Script_AnimStepLoop();
    EMI_ArchiveLoad(EMI_SLOT_BATL_RET);
    TASK(PartyMember)->unk_03 += 1;
}

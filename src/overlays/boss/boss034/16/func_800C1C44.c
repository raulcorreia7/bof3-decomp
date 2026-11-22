#include "boss034_16.h"

MATCH void func_800C1C44(void) {
    Area_SelectSceneRecord(0x1C1);
    ((PartyMember*)g_Task)->unk_2A = 1;
    Script_Select(8U);
    ((PartyMember*)g_Task)->unk_24 &= 0x77;
    Script_AnimStepLoop();
    EMI_ArchiveLoad(EMI_SLOT_BATL_RET);
    ((PartyMember*)g_Task)->unk_03 += 1;
}

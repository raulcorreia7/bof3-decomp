#include "boss034_16.h"

MATCH void func_800C1C44(void) {
    Area_SelectSceneRecord(0x1C1);
    ((PartyMember*)g_Task)->unk_2A = 1;
    Actor_SelectScript(8U);
    ((PartyMember*)g_Task)->unk_24 &= 0x77;
    Actor_StepAnimLoop();
    EMI_LoadArchive(4);
    ((PartyMember*)g_Task)->unk_03 += 1;
}

#include "boss034_16.h"

MATCH void func_800C1C44(void) {
    Area_FindSceneRecord(0x1C1);
    ((PartyBattler*)g_SpadWork)->unk_2A = 1;
    Actor_SelectScript(8U);
    ((PartyBattler*)g_SpadWork)->unk_24 &= 0x77;
    func_8014D978();
    EMI_LoaderStreamInitSlot(4);
    ((PartyBattler*)g_SpadWork)->unk_03 += 1;
}

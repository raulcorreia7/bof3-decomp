#include "boss008_16.h"

MATCH void func_800C1B48(void) {
    u32 temp_v0_2;
    u32 temp_v0_3;
    u8  temp_v0;

    func_800C236C(((PartyBattler*)g_SpadWork)->unk_09);
    temp_v0 = ((PartyBattler*)g_SpadWork)->unk_09;
    if (temp_v0 == 0) {
        ((PartyBattler*)g_SpadWork)->unk_48 = 0;
        Area_FindSceneRecord(0x83);
        Actor_SelectScript(0U);
        func_801E54EC();
        ((PartyBattler*)g_SpadWork)->flags_00 &= 0xBF;
        ((PartyBattler*)g_SpadWork)->step_01 = 6;
        ((PartyBattler*)g_SpadWork)->unk_02  = 4;
        ((PartyBattler*)g_SpadWork)->unk_03 += 1;
        ((PartyBattler*)g_SpadWork)->unk_04 = 0;
        return;
    }
    ((PartyBattler*)g_SpadWork)->unk_09 = temp_v0 - 4;
    temp_v0_2                           = ((PartyBattler*)g_SpadWork)->unk_40;
    if ((s32)temp_v0_2 > 0) {
        ((PartyBattler*)g_SpadWork)->unk_40 = temp_v0_2 - 0x2000;
    } else {
        ((PartyBattler*)g_SpadWork)->unk_40 = 0;
    }
    temp_v0_3 = ((PartyBattler*)g_SpadWork)->unk_44;
    if ((s32)temp_v0_3 > 0) {
        ((PartyBattler*)g_SpadWork)->unk_44 = temp_v0_3 - 0x2000;
        return;
    }
    ((PartyBattler*)g_SpadWork)->unk_44 = 0;
}

#include "boss028_16.h"

MATCH void func_800C2024(void) {
    s32 temp_a1;

    ((PartyBattler*)g_Task)->unk_24 = 0;
    ((PartyBattler*)g_Task)->unk_2A = 0;
    ((PartyBattler*)g_Task)->unk_48 = 0;
    ((PartyBattler*)g_Task)->unk_29 = 5;
    Area_FindSceneRecord(0x15C);
    Actor_SelectScript(6U);
    ((PartyBattler*)g_Task)->pos.x.fixed      = D_801EB4E0->pos.x.fixed;
    temp_a1                                   = D_801EB4E0->pos.y.fixed;
    ((PartyBattler*)g_Task)->pos.y.fixed      = temp_a1;
    COORD_INT(((PartyBattler*)g_Task)->pos.z) = Area_SampleHeight(((PartyBattler*)g_Task)->pos.x.fixed, temp_a1);
    ((PartyBattler*)g_Task)->step += 1;
}

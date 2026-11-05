#include "boss028_16.h"

MATCH void func_800C2024(void) {
    s32 temp_a1;

    ((PartyBattler*)g_Task)->unk_24 = 0;
    ((PartyBattler*)g_Task)->unk_2A = 0;
    ((PartyBattler*)g_Task)->unk_48 = 0;
    ((PartyBattler*)g_Task)->unk_29 = 5;
    Area_FindSceneRecord(0x15C);
    Actor_SelectScript(6U);
    ((PartyBattler*)g_Task)->pos.x.raw     = D_801EB4E0->pos.x.raw;
    temp_a1                                = D_801EB4E0->pos.y.raw;
    ((PartyBattler*)g_Task)->pos.y.raw     = temp_a1;
    ((PartyBattler*)g_Task)->pos.z.half.hi = Area_SampleHeight(((PartyBattler*)g_Task)->pos.x.raw, temp_a1);
    ((PartyBattler*)g_Task)->step += 1;
}

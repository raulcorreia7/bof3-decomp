#include "boss028_16.h"

MATCH void func_800C2024(void) {
    s32 temp_a1;

    ((PartyBattler*)g_SpadWork)->unk_24 = 0;
    ((PartyBattler*)g_SpadWork)->unk_2A = 0;
    ((PartyBattler*)g_SpadWork)->unk_48 = 0;
    ((PartyBattler*)g_SpadWork)->unk_29 = 5;
    Area_FindSceneRecord(0x15C);
    Actor_SelectScript(6U);
    ((PartyBattler*)g_SpadWork)->coord_x_34.raw = D_801EB4E0->coord_x_34.raw;
    temp_a1                                     = D_801EB4E0->coord_y_38.raw;
    ((PartyBattler*)g_SpadWork)->coord_y_38.raw = temp_a1;
    ((PartyBattler*)g_SpadWork)->word_3C.half.span_3E =
        Area_SampleHeight(((PartyBattler*)g_SpadWork)->coord_x_34.raw, temp_a1);
    ((PartyBattler*)g_SpadWork)->unk_02 += 1;
}

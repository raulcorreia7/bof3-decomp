#include "boss004_13.h"

MATCH void func_800C1A4C(void) {
    u8* result;
    u8  temp_v0;

    temp_v0                                          = ((PartyBattler*)g_SpadWork)->word_08.byte.unk_09 - 1;
    ((PartyBattler*)g_SpadWork)->word_08.byte.unk_09 = temp_v0;
    if (!(temp_v0 & 0xFF)) {
        Area_FindSceneRecord(0x5F);
        if (g_BattleEncounter == 5) {
            ((PartyBattler*)g_SpadWork)->unk_2A = 0;
            ((PartyBattler*)g_SpadWork)->coord_y_38.raw += 0x18000;
        } else {
            ((PartyBattler*)g_SpadWork)->unk_2A = 1;
            ((PartyBattler*)g_SpadWork)->coord_x_34.raw += 0x18000;
        }
        ((PartyBattler*)g_SpadWork)->word_3C.half.span_3E =
            Area_SampleHeight(((PartyBattler*)g_SpadWork)->coord_x_34.raw, ((PartyBattler*)g_SpadWork)->coord_y_38.raw);
        g_BattleCurrentEnemy->script = &D_800C272C;
        Actor_SelectScript(1U);
        result = &g_BattleResult;
        *result |= 4;
        g_BattleBossFlags |= 1 << ((PartyBattler*)g_SpadWork)->slot;
        ((PartyBattler*)g_SpadWork)->unk_02 += 1;
    }
    func_8014D978();
}

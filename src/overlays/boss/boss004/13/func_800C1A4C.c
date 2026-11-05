#include "boss004_13.h"

MATCH void func_800C1A4C(void) {
    u8* result;
    u8  temp_v0;

    temp_v0                         = ((PartyBattler*)g_Task)->unk_09 - 1;
    ((PartyBattler*)g_Task)->unk_09 = temp_v0;
    if (!(temp_v0 & 0xFF)) {
        Area_FindSceneRecord(0x5F);
        if (g_BattleEncounter == 5) {
            ((PartyBattler*)g_Task)->unk_2A = 0;
            ((PartyBattler*)g_Task)->pos.y.fixed += 0x18000;
        } else {
            ((PartyBattler*)g_Task)->unk_2A = 1;
            ((PartyBattler*)g_Task)->pos.x.fixed += 0x18000;
        }
        COORD_INT(((PartyBattler*)g_Task)->pos.z) =
            Area_SampleHeight(((PartyBattler*)g_Task)->pos.x.fixed, ((PartyBattler*)g_Task)->pos.y.fixed);
        g_BattleCurrentEnemy->script = &D_800C272C;
        Actor_SelectScript(1U);
        result = &g_BattleResult;
        *result |= 4;
        g_BattleBossFlags |= 1 << ((PartyBattler*)g_Task)->slot;
        ((PartyBattler*)g_Task)->step += 1;
    }
    func_8014D978();
}

#include "boss028_16.h"

MATCH void func_800C2024(void) {
    s32 y;

    ((PartyMember*)g_Task)->unk_24 = 0;
    ((PartyMember*)g_Task)->unk_2A = 0;
    ((PartyMember*)g_Task)->unk_48 = 0;
    ((PartyMember*)g_Task)->unk_29 = 5;
    Area_SelectSceneRecord(0x15C);
    Actor_SelectScript(6U);
    ((PartyMember*)g_Task)->pos.x.fixed      = g_BattleEffectBattler->pos.x.fixed;
    y                                        = g_BattleEffectBattler->pos.y.fixed;
    ((PartyMember*)g_Task)->pos.y.fixed      = y;
    COORD_INT(((PartyMember*)g_Task)->pos.z) = Area_SampleHeight(((PartyMember*)g_Task)->pos.x.fixed, y);
    ((PartyMember*)g_Task)->header.step += 1;
}

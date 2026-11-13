#include "boss004_13.h"

MATCH void func_800C1A4C(void) {
    u8* result;
    u8  timer;

    timer                          = ((PartyMember*)g_Task)->unk_09 - 1;
    ((PartyMember*)g_Task)->unk_09 = timer;
    if (!(timer & BYTE_MASK)) {
        Area_SelectSceneRecord(0x5F);
        if (g_Battle.encounter == 5) {
            ((PartyMember*)g_Task)->unk_2A = 0;
            ((PartyMember*)g_Task)->pos.y.fixed += TO_COORD(1) + COORD_HALF;
        } else {
            ((PartyMember*)g_Task)->unk_2A = 1;
            ((PartyMember*)g_Task)->pos.x.fixed += TO_COORD(1) + COORD_HALF;
        }
        COORD_INT(((PartyMember*)g_Task)->pos.z) = Area_SampleHeight(((PartyMember*)g_Task)->pos.x.fixed, ((PartyMember*)g_Task)->pos.y.fixed);
        g_BattleCurrentEnemy->script             = &D_800C272C;
        Actor_SelectScript(1U);
        result = &g_Battle.outcome.result;
        *result |= 4;
        g_Battle.boss_flags |= 1 << ((PartyMember*)g_Task)->slot;
        ((PartyMember*)g_Task)->header.step += 1;
    }
    Actor_StepAnimLoop();
}

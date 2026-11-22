#include "boss004_13.h"

MATCH void func_800C1A4C(void) {
    u8* result;
    u8  timer;

    timer                     = TASK(PartyMember)->unk_09 - 1;
    TASK(PartyMember)->unk_09 = timer;
    if (!(timer & BYTE_MASK)) {
        Area_SceneSelectRecord(0x5F);
        if (g_Battle.encounter == 5) {
            TASK(PartyMember)->unk_2A = 0;
            TASK(PartyMember)->pos.y.fixed += TO_COORD(1) + COORD_HALF;
        } else {
            TASK(PartyMember)->unk_2A = 1;
            TASK(PartyMember)->pos.x.fixed += TO_COORD(1) + COORD_HALF;
        }
        COORD_INT(TASK(PartyMember)->pos.z) = Area_HeightSample(TASK(PartyMember)->pos.x.fixed, TASK(PartyMember)->pos.y.fixed);
        g_BattleCurrentEnemy->script        = &D_800C272C;
        Script_Select(1U);
        result = &g_Battle.outcome.result;
        *result |= 4;
        g_Battle.boss_flags |= 1 << TASK(PartyMember)->slot;
        TASK(PartyMember)->header.step += 1;
    }
    Script_AnimStepLoop();
}

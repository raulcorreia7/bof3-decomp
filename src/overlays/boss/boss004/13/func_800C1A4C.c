#include "boss004_13.h"

MATCH void func_800C1A4C(void) {
    u8* result;
    u8  timer;

    timer                     = SELF(PartyMember)->unk_09 - 1;
    SELF(PartyMember)->unk_09 = timer;
    if (!(timer & BYTE_MASK)) {
        Area_SceneSelectRecord(0x5F);
        if (g_Battle.encounter == 5) {
            SELF(PartyMember)->unk_2A = 0;
            SELF(PartyMember)->pos.y.fixed += TO_COORD(1) + COORD_HALF;
        } else {
            SELF(PartyMember)->unk_2A = 1;
            SELF(PartyMember)->pos.x.fixed += TO_COORD(1) + COORD_HALF;
        }
        COORD_INT(SELF(PartyMember)->pos.z) = Area_HeightSample(SELF(PartyMember)->pos.x.fixed, SELF(PartyMember)->pos.y.fixed);
        g_BattleCurrentEnemy->script        = &D_800C272C;
        Script_Select(1U);
        result = &g_Battle.outcome.result;
        *result |= 4;
        g_Battle.boss_flags |= 1 << SELF(PartyMember)->slot;
        SELF(PartyMember)->header.step += 1;
    }
    Script_AnimStepLoop();
}

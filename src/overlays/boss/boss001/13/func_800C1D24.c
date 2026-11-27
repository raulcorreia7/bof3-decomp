#include "boss001_13.h"

MATCH void func_800C1D24(void) {
    volatile u16* counter;
    u16           timer;
    s32           value;

    counter  = &D_801463BE;
    timer    = *counter - 1;
    *counter = timer;
    if (timer == 0) {
        value                               = SELF(PartyMember)->pos.y.fixed + COORD_HALF;
        SELF(PartyMember)->pos.y.fixed      = value;
        COORD_INT(SELF(PartyMember)->pos.z) = Area_HeightSample(SELF(PartyMember)->pos.x.fixed, value);
        Area_SceneSelectRecord(0x5F);
        g_BattleCurrentEnemy->script = &D_800C21A0;
        SELF(PartyMember)->unk_2A    = 0;
        Script_Select(0U);
        SELF(PartyMember)->header.step += 1;
    }
    Script_AnimStepLoop();
}

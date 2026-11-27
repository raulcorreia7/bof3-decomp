#include "boss001_13.h"

MATCH void func_800C1A08(void) {
    s32 value;

    if (D_801463BE == 0) {
        value                               = SELF(PartyMember)->pos.y.fixed + COORD_HALF;
        SELF(PartyMember)->pos.y.fixed      = value;
        COORD_INT(SELF(PartyMember)->pos.z) = Area_HeightSample(SELF(PartyMember)->pos.x.fixed, value);
        Area_SceneSelectRecord(0x5F);
        g_BattleCurrentEnemy->script = &D_800C2188;
        SELF(PartyMember)->unk_2A    = 0;
        Script_Select(1U);
        g_BattleResult |= 4;
        Area_CellSetPalette(100, 20);
        SELF(PartyMember)->header.step += 1;
    }
    Script_AnimStepLoop();
}

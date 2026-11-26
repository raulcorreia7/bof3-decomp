#include "boss028_16.h"

MATCH void func_800C2024(void) {
    s32 y;

    SELF(PartyMember)->unk_24 = 0;
    SELF(PartyMember)->unk_2A = 0;
    SELF(PartyMember)->unk_48 = 0;
    SELF(PartyMember)->unk_29 = 5;
    Area_SceneSelectRecord(0x15C);
    Script_Select(6U);
    SELF(PartyMember)->pos.x.fixed      = g_BattleEffectBattler->pos.x.fixed;
    y                                   = g_BattleEffectBattler->pos.y.fixed;
    SELF(PartyMember)->pos.y.fixed      = y;
    COORD_INT(SELF(PartyMember)->pos.z) = Area_HeightSample(SELF(PartyMember)->pos.x.fixed, y);
    SELF(PartyMember)->header.step += 1;
}
